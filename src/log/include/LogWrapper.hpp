#ifndef _LOG_WRAPPER_HPP_
#define _LOG_WRAPPER_HPP_

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define USE_CONSOLE

#define LogTrace(...) spdlog::trace(__VA_ARGS__)
#define LogDebug(...) spdlog::debug(__VA_ARGS__)
#define LogInfo(...) spdlog::info(__VA_ARGS__)
#define LogWarn(...) spdlog::warn(__VA_ARGS__)
#define LogError(...) spdlog::error(__VA_ARGS__)
#define LogCritical(...) spdlog::critical(__VA_ARGS__)

typedef spdlog::level::level_enum LogLevel;

#define LOGPATH "logs/daily.txt"
#define LOGGERNAME "logger"

class LogWrapper
{
public:
    LogWrapper(const LogWrapper&) = delete;
    LogWrapper& operator=(const LogWrapper&) = delete;
    static LogWrapper& Instance();

    void Init();
    void SetLevel(LogLevel level);
private:
    LogWrapper();
    virtual ~LogWrapper();
};

#endif /* _LOG_WRAPPER_HPP_ */