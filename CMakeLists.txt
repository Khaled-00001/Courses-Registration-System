cmake_minimum_required(VERSION 4.0)
project(course_regestiration)

set(CMAKE_CXX_STANDARD 20)

add_executable(course_regestiration main.cpp
        Course.cpp
        Course.h)
