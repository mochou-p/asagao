// asagao/includes/benchmark.hpp


#pragma once


#include "stdafx.h"


using time_point = std::chrono::_V2::system_clock::time_point;


class Benchmark
{
public:
    Benchmark(c_cstr name);
    ~Benchmark();
private:
    time_point m_start = std::chrono::high_resolution_clock::now();
    c_cstr     m_name;
};
