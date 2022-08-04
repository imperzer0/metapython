cmake_minimum_required(VERSION 3.22)
project(metapython)

set(CMAKE_CXX_STANDARD 20)

if (NOT ("${APP_VERSION}" STREQUAL ""))
    message("APP_VERSION = ${APP_VERSION}")
    add_compile_definitions(metapython APPLICATION_VERSION="${APP_VERSION}")
endif ()

if (NOT ("${APP_NAME}" STREQUAL ""))
    message("APP_NAME = ${APP_NAME}")
    add_compile_definitions(metapython APPLICATION_NAME="${APP_NAME}")
endif ()

add_executable(metapython main.cpp pycompile.hpp pyexec.hpp helpers.hpp defines.h parsed_arguments.h parsed_arguments.cpp)
add_executable(tests tests.cpp pycompile.hpp pyexec.hpp helpers.hpp defines.h parsed_arguments.h parsed_arguments.cpp)

target_link_libraries(metapython python3.10)
target_link_libraries(tests python3.10)