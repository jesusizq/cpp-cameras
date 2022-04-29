#include <Logger.hpp>
#include <MotionRecorderApp.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  if (argc < 5 || argc > 6) {
    Logger::log("Usage: " + std::string(argv[0]) +
                    " <camera_uri> <dest_host_ip> <dest_port> <time_to_stop> "
                    "[<output_path>]",
                Logger::LogLevel::ERROR);
    return -1;
  }

  std::string cameraUri{argv[1]};
  std::string destHost{argv[2]};
  std::string destPort{argv[3]};
  double timeToStop = std::atof(argv[4]);
  std::string outputPath;

  if (argc == 6) {
    outputPath = argv[5];
  };

  Logger::log("Starting MotionRecorderApp for [" + cameraUri + "] at [" +
                  destHost + ":" + destPort + "]",
              Logger::LogLevel::INFO);
  MotionRecorderApp app(cameraUri, destHost, destPort, timeToStop, outputPath);
  app.run();

  return 0;
}
