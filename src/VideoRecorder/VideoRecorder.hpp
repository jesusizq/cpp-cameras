
#ifndef VIDEORECORDER_HPP
#define VIDEORECORDER_HPP

#include <opencv2/opencv.hpp>
#include <string>

enum class OutputMode { FILE, UDP };

class VideoRecorder {
public:
  VideoRecorder() = delete;
  VideoRecorder(std::string_view outputSettings, float fps, int width,
                int height, OutputMode outputMode = OutputMode::FILE);
  ~VideoRecorder() { writer.release(); }
  VideoRecorder(const VideoRecorder &) = delete;
  VideoRecorder &operator=(const VideoRecorder &) = delete;
  VideoRecorder(VideoRecorder &&) = delete;
  VideoRecorder &operator=(VideoRecorder &&) = delete;

  bool open();
  void writeFrame(const cv::Mat &frame) { writer.write(frame); }

private:
  cv::VideoWriter writer;
  std::string outputSettings;
  float fps;
  int width;
  int height;
  OutputMode outputMode{OutputMode::FILE};
};

#endif // VIDEORECORDER_HPP
