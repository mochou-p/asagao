// asagao/source/benchmark.cpp


#include "stdafx.h"

#include "benchmark.hpp"


Benchmark::Benchmark
(c_cstr name)
: m_name{name}
{}

Benchmark::~Benchmark()
{
    time_point end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - m_start);

    std::cout << "[BENCHMARK] ["
              << m_name
              << "]\t"
              << duration.count() * 0.001f
              << " ms"
              << std::endl;
}
