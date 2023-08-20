// asagao/source/utils.cpp


#include "utils.hpp"

void quit(const std::string& t_message)
{
    std::cerr << t_message << std::endl;
    exit(EXIT_FAILURE);
}

void opengl_check_error
(GLuint t_id, GLint t_status, const std::string& t_message,
    opengl_iv_func* t_iv_func, opengl_info_log_func* t_info_func)
{
    GLint success;
    (*t_iv_func)(t_id, t_status, &success);

    if (!success)
    {
        char  error[OPENGL_ERROR_LEN];
        (*t_info_func)(t_id, OPENGL_ERROR_LEN, nullptr, error);
        std::cerr << t_message << " failed" << std::endl << error
            << std::endl;
        exit(EXIT_FAILURE);
    }
}
