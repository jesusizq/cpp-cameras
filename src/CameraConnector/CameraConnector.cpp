#include <CameraConnector.hpp>
#include <iostream>

CameraConnector::CameraConnector(const std::string &cameraUri)
    : cameraUri(cameraUri) {}

bool CameraConnector::open() {
  cap.open(cameraUri.c_str());
  if (!cap.isOpened()) {
    return false;
  }

  connectorReady = true;
  return true;
}
