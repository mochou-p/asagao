// asagao/source/log.cpp


#include <iostream>
#include <ctime>
#include <sstream>
#include "log.hpp"
#include "glad/glad.h"

#define WHITE "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

#define LEADING_ZEROS(x) (x < 10 ? "0" : "") << x

void
Log::automatic
(
 const std::string& file,
       unsigned int line,
       unsigned int severity,
 const std::string& message
)
{
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            info(file, line, message);
            break;  
        case GL_DEBUG_SEVERITY_LOW:
        case GL_DEBUG_SEVERITY_MEDIUM:
            warn(file, line, message);
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            fatal(file, line, message);
            break;
        default:
            warn(file, line, "unknown log severity level");
            break;
    }
}

static std::string
now()
{
    std::time_t epoch    = std::time(nullptr);
    std::tm*    time_now = std::localtime(&epoch);

    std::stringstream ss;
    ss << "["
       << LEADING_ZEROS(time_now->tm_hour)
       << ":"
       << LEADING_ZEROS(time_now->tm_min)
       << ":"
       << LEADING_ZEROS(time_now->tm_sec)
       << "]";

    return ss.str();
}

static std::string
header
(
 const std::string& file,
       unsigned int line
)
{
    std::stringstream ss;
    ss << now()
       << " ["
       << file
       << ":"
       << line
       << "]\t";

    return ss.str();
}

void
Log::info
(
 const std::string& file,
       unsigned int line,
 const std::string& message
)
{
    std::cout << BLUE << header(file, line) << message << std::endl;
}

void
Log::warn
(
 const std::string& file,
       unsigned int line,
 const std::string& message
)
{
    std::cout << YELLOW << header(file, line) << message << WHITE << std::endl;
}

void
Log::error
(
 const std::string& file,
       unsigned int line,
 const std::string& message
)
{
    std::cout << RED << header(file, line) << message << WHITE << std::endl;
}

void
Log::fatal
(
 const std::string& file,
       unsigned int line,
 const std::string& message
)
{
    std::cerr << RED << header(file, line) << message << WHITE << std::endl;

    exit(EXIT_FAILURE);
}
