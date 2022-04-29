#include <VideoRecorder.hpp>
#include <iostream>

VideoRecorder::VideoRecorder(std::string_view outputSettings, float fps,
                             int width, int height, OutputMode outputMode)
    : outputSettings(outputSettings), fps(fps), width(width), height(height),
      outputMode(outputMode) {}

bool VideoRecorder::open() {
  switch (outputMode) {
  case OutputMode::FILE:
    writer.open(outputSettings, cv::VideoWriter::fourcc('X', '2', '6', '4'),
                fps, cv::Size(width, height), true);
    break;
  case OutputMode::UDP:
    writer.open(outputSettings, cv::CAP_GSTREAMER, fps, cv::Size(width, height),
                true);
    break;
  }

  if (!writer.isOpened()) {
    return false;
  }

  return true;
}
