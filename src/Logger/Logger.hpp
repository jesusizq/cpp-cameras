#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>
#include <string>

class Logger {
public:
  enum class LogLevel { INFO, ERROR };

  static void log(std::string_view message, LogLevel level = LogLevel::INFO);

private:
  static std::string getCurrentTime();
  static std::ostream &getStream(LogLevel level);
  static std::string logLevelToString(LogLevel level);
};

#endif // LOGGER_HPP
