cmake_minimum_required(VERSION 3.29)
project(cache-play CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(cache-play main.cpp)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(external/benchmark)
target_link_libraries(cache-play benchmark::benchmark)
target_compile_options(cache-play PUBLIC -O3 -march=native -funroll-loops)

if (MSVC)
    target_compile_options(cache-play PUBLIC /W4)
else ()
    target_compile_options(cache-play PUBLIC -Werror -Wall -Wextra -Wpedantic -Wconversion)
endif ()