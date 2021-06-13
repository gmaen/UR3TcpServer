#include "LogWrapper.hpp"

LogWrapper::LogWrapper() {}
LogWrapper::~LogWrapper() 
{
    spdlog::shutdown();
}

LogWrapper& LogWrapper::Instance()
{
    static LogWrapper instance;
    return instance;
}

void LogWrapper::Init()
{
    std::vector<spdlog::sink_ptr> sinks;

#ifdef USE_CONSOLE
    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console->set_level(LogLevel::trace);
    sinks.push_back(console);
#endif /* USE_CONSOLE */
    auto daily = std::make_shared<spdlog::sinks::daily_file_sink_st>(LOGPATH, 00, 00);
    daily->set_level(LogLevel::info);
    sinks.push_back(daily);

    auto logger = std::make_shared<spdlog::logger>(LOGGERNAME, begin(sinks), end(sinks));
    logger->flush_on(LogLevel::info);

    spdlog::set_default_logger(logger);

    SetLevel(LogLevel::trace);
}

void LogWrapper::SetLevel(LogLevel level)
{
    spdlog::set_level(level);
}