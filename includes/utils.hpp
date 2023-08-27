// asagao/includes/utils.hpp


#pragma once
#ifndef __utils_hpp_
#define __utils_hpp_

#include <string>

using opengl_iv_func       = void (*)(unsigned int, unsigned int, int*);
using opengl_info_log_func = void (*)(unsigned int, int, int*, char*);

void quit(const std::string&);

void opengl_check_error(unsigned int, int, const std::string&,
    opengl_iv_func*, opengl_info_log_func*);

#endif  // __utils_hpp_
