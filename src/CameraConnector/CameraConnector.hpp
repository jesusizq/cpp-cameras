#ifndef CAMERACONNECTOR_HPP
#define CAMERACONNECTOR_HPP

#include <opencv2/opencv.hpp>
#include <string>

class CameraConnector {
public:
  CameraConnector() = delete;
  CameraConnector(const std::string &cameraUri);
  ~CameraConnector() { cap.release(); }
  CameraConnector(const CameraConnector &) = delete;
  CameraConnector &operator=(const CameraConnector &) = delete;
  CameraConnector(CameraConnector &&) = delete;
  CameraConnector &operator=(CameraConnector &&) = delete;

  bool open();
  bool isReady() const { return connectorReady; };
  bool getFrame(cv::Mat &frame) { return cap.read(frame); }
  float getFPS() const { return cap.get(cv::CAP_PROP_FPS); }
  int getWidth() const { return cap.get(cv::CAP_PROP_FRAME_WIDTH); }
  int getHeight() const { return cap.get(cv::CAP_PROP_FRAME_HEIGHT); }

private:
  cv::VideoCapture cap;
  std::string cameraUri;
  bool connectorReady{false};
};

#endif // CAMERACONNECTOR_HPP
