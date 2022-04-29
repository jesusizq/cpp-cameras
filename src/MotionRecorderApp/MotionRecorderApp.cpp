#include <GStreamerPipeline.hpp>
#include <Logger.hpp>
#include <MotionDetector.hpp>
#include <MotionRecorderApp.hpp>

#include <chrono>
#include <iostream>

MotionRecorderApp::MotionRecorderApp(const std::string &cameraUri,
                                     const std::string &destHost,
                                     const std::string &destPort,
                                     double timeToStop,
                                     const std::string &outputPath)
    : cameraUri(cameraUri), destHost(destHost), destPort(destPort),
      timeToStop(timeToStop), outputPath(outputPath),
      cameraConnector(cameraUri) {}

std::string MotionRecorderApp::getOutputSettings() {
  std::string outputSettings = outputPath;
  if (outputSettings.empty()) {
    outputMode = OutputMode::UDP;
    outputSettings = "appsrc ! videoconvert ! videoscale ! "
                     "video/x-raw ! x264enc !mpegtsmux "
                     "!udpsink host=" +
                     destHost + " port=" + destPort + " sync=false ";
  } else if (!isValidPath(outputPath)) {
    Logger::log("Invalid output path.", Logger::LogLevel::ERROR);
    return "";
  }

  return outputSettings;
}
void MotionRecorderApp::run() {

  std::thread captureThread(&MotionRecorderApp::captureFrames, this);
  std::thread processThread(&MotionRecorderApp::processFrames, this);

  captureThread.join();
  processThread.join();
}

void MotionRecorderApp::captureFrames() {
  while (!cameraConnector.open() || !cameraConnector.isReady()) {
    Logger::log("Failed to open camera. Let's try again.",
                Logger::LogLevel::ERROR);
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }

  Logger::log("Camera connection established and capturing video.",
              Logger::LogLevel::INFO);

  cv::Mat frame;
  isCapturing = true;

  while (isCapturing) {
    if (!cameraConnector.getFrame(frame) || frame.empty()) {
      isCapturing = false;
      break;
    }

    frameQueue.push(frame);
  }
}

void MotionRecorderApp::processFrames() {
  using namespace std::chrono_literals;

  GStreamerPipeline pipeline{"rtspsrc location=" + cameraUri +
                             " ! decodebin ! videoconvert ! x264enc "
                             "tune=zerolatency ! rtph264pay ! "
                             "udpsink host=" +
                             destHost + " + port=" + destPort};

  while (!pipeline.initialize()) {
    Logger::log("Failed to initialize GStreamer pipeline. Let's try again.",
                Logger::LogLevel::ERROR);
    std::this_thread::sleep_for(10s);
  }

  Logger::log("GStreamer pipeline initialized.", Logger::LogLevel::INFO);

  while (!cameraConnector.isReady()) {
    std::this_thread::sleep_for(10s);
  }

  auto fps = cameraConnector.getFPS();
  auto width = cameraConnector.getWidth();
  auto height = cameraConnector.getHeight();

  if (width % 4 || height % 2) {
    Logger::log("Dimensions not supported.", Logger::LogLevel::ERROR);
    return;
  }

  auto outputSettings = getOutputSettings();
  if (outputSettings.empty()) {
    return;
  }

  VideoRecorder videoRecorder{outputSettings, fps, width, height, outputMode};
  if (!videoRecorder.open()) {
    Logger::log(
        "Failed to open VideoWriter. Check if the output settings are correct.",
        Logger::LogLevel::ERROR);
    return;
  }

  Logger::log("VideoWriter correctly opened.", Logger::LogLevel::INFO);
  Logger::log("Starting GStreamer pipeline.", Logger::LogLevel::INFO);
  pipeline.start();

  MockMotionDetector<cv::Mat> motionDetector;
  cv::Mat frame;
  cv::Mat prevFrame;
  bool motionDetected = false;
  bool finishRecording = false;
  auto lastMotionTime = std::chrono::steady_clock::now();

  Logger::log("MotionRecorderApp is ready to get frames.",
              Logger::LogLevel::INFO);

  bool finishLoop = false;
  while (!finishLoop) {
    auto success = frameQueue.tryPop(frame);
    if (!success) {
      std::this_thread::sleep_for(10ms);
      continue;
    }

    auto motion = motionDetector.detect(prevFrame, frame);
    if (motion == Motion::MOTION) {
      if (!motionDetected) {
        Logger::log("Motion detected. Start recording.",
                    Logger::LogLevel::INFO);
        motionDetected = true;
      }

      lastMotionTime = std::chrono::steady_clock::now();

    } else if (motionDetected) {
      auto currentTime = std::chrono::steady_clock::now();
      std::chrono::duration<double> elapsedTime = currentTime - lastMotionTime;

      if (elapsedTime.count() >= timeToStop) {
        finishRecording = true;
        Logger::log("No motion detected for " + std::to_string(timeToStop) +
                        " seconds. Stop recording.",
                    Logger::LogLevel::INFO);
      }
    }

    if (motionDetected) {
      videoRecorder.writeFrame(frame);
      prevFrame = std::move(frame);
      if (finishRecording) {
        finishLoop = true;
      }
    }
  }

  pipeline.stop();
  isCapturing = false;
  Logger::log("GStreamer pipeline stopped.", Logger::LogLevel::INFO);
}
