cmake_minimum_required(VERSION 3.13)
project(rt)

file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(rt ${SRC})

target_compile_options(rt PRIVATE /std:c++17)
target_include_directories(rt PRIVATE "src/")

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(rt OpenMP::OpenMP_CXX)
endif()