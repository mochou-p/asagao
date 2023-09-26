// asagao/includes/log.hpp


#pragma once

#define LOG_AUTO(s, m) Log::automatic(__FILE__, __LINE__, s, m)
#define LOG_INFO(m) Log::info(__FILE__, __LINE__, m)
#define LOG_WARN(m) Log::warn(__FILE__, __LINE__, m)
#define LOG_ERROR(m) Log::error(__FILE__, __LINE__, m)
#define LOG_FATAL(m) Log::fatal(__FILE__, __LINE__, m)

class Log
{
public:
    static void automatic(const str& file, u32 line, u32 severity, const str& message);

    static void      info(const str& file, u32 line, const str& message);
    static void      warn(const str& file, u32 line, const str& message);
    static void     error(const str& file, u32 line, const str& message);
    static void     fatal(const str& file, u32 line, const str& message);
};
