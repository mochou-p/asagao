// asagao/source/utils.cpp


#include <iostream>
#include "utils.hpp"

#define OPENGL_ERROR_LEN 512

void
quit(const std::string& message)
{
    std::cerr << message << std::endl;
    exit(EXIT_FAILURE);
}

void
opengl_check_error(      GLuint                id,
                         GLint                 status,
                   const std::string&          message,
                         opengl_iv_func*       iv_func,
                         opengl_info_log_func* info_func)
{
    GLint success;
    (*iv_func)(id, status, &success);

    if (!success)
    {
        char error[OPENGL_ERROR_LEN];
        (*info_func)(id, OPENGL_ERROR_LEN, nullptr, error);
        std::cerr << message << " failed" << std::endl << error
            << std::endl;
        exit(EXIT_FAILURE);
    }
}
