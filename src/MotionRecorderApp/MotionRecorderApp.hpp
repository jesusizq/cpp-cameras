#ifndef MOTIONRECORDERAPP_HPP
#define MOTIONRECORDERAPP_HPP

#include "opencv2/opencv.hpp"
#include <CameraConnector.hpp>
#include <FrameQueue.hpp>
#include <VideoRecorder.hpp>
#include <filesystem>
#include <string>

class MotionRecorderApp {
public:
  MotionRecorderApp() = delete;
  MotionRecorderApp(const std::string &cameraUri, const std::string &destHost,
                    const std::string &destPort, double timeToStop,
                    const std::string &outputPath = "");
  void run();

private:
  std::string cameraUri;
  std::string destHost;
  std::string destPort;
  std::string outputPath;
  double timeToStop;
  FrameQueue<cv::Mat> frameQueue;
  CameraConnector cameraConnector;
  OutputMode outputMode{OutputMode::FILE};
  bool isCapturing{false};

  void processFrames();
  void captureFrames();
  std::string getOutputSettings();
  bool isValidPath(std::string_view path) const {
    return !path.empty() &&
           std::filesystem::exists(std::filesystem::path(path).parent_path());
  }
};

#endif // MOTIONRECORDERAPP_HPP
