cmake_minimum_required(VERSION 3.9)
project(benchmark LANGUAGES CXX)

find_package(OpenMP REQUIRED)
add_executable(benchmark openmp-synch-benchmark.cpp)
target_link_libraries(benchmark PRIVATE OpenMP::OpenMP_CXX)