// asagao/includes/log.hpp


#pragma once

#include <string>

#define LOG_AUTO(s, m) Log::automatic(__FILE__, __LINE__, s, m)
#define LOG_INFO(m) Log::info(__FILE__, __LINE__, m)
#define LOG_WARN(m) Log::warn(__FILE__, __LINE__, m)
#define LOG_ERROR(m) Log::error(__FILE__, __LINE__, m)
#define LOG_FATAL(m) Log::fatal(__FILE__, __LINE__, m)

class Log
{
public:
    static void automatic
    (
     const std::string& file,
           unsigned int line,
           unsigned int severity,
     const std::string& message
    );

    static void info
    (
     const std::string& file,
           unsigned int line,
     const std::string& message
    );

    static void warn
    (
     const std::string& file,
           unsigned int line,
     const std::string& message
    );

    static void error
    (
     const std::string& file,
           unsigned int line,
     const std::string& message
    );

    static void fatal
    (
     const std::string& file,
           unsigned int line,
     const std::string& message
    );
};
