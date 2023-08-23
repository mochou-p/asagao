// asagao/includes/utils.hpp


#pragma once
#ifndef __utils_hpp_
#define __utils_hpp_

#include <string>
#include "glad/glad.h"

using opengl_iv_func       = void (*)(GLuint, GLenum, GLint*);
using opengl_info_log_func = void (*)(GLuint, GLsizei, GLsizei*, GLchar*);

void quit(const std::string&);

void opengl_check_error(GLuint, GLint, const std::string&, opengl_iv_func*,
    opengl_info_log_func*);

#endif  // __utils_hpp_
