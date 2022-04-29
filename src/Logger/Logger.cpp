#include "Logger.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>

std::ostream &Logger::getStream(LogLevel level) {
  if (level == LogLevel::ERROR) {
    return std::cerr;
  }
  return std::cout;
}

std::string Logger::getCurrentTime() {
  std::time_t now{std::time(nullptr)};
  std::tm *localTime{std::localtime(&now)};
  std::stringstream ss;
  ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

void Logger::log(std::string_view message, LogLevel level) {
  std::ostream &stream = getStream(level);
  stream << "[" << getCurrentTime() << "][" << logLevelToString(level)
         << "]: " << message << std::endl;
}

std::string Logger::logLevelToString(LogLevel level) {
  switch (level) {
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::ERROR:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}
