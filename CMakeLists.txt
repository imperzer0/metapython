cmake_minimum_required(VERSION 3.22)
project(metapython)

set(CMAKE_CXX_STANDARD 20)

add_executable(metapython main.cpp pycompile.hpp pyexec.hpp get_current_time.hpp)

target_link_libraries(metapython python3.10)