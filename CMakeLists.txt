cmake_minimum_required(VERSION 3.30)
project(course_regestiration)

set(CMAKE_CXX_STANDARD 17)

add_executable(course_regestiration
        main.cpp
        Course.cpp
        Student.cpp
        Admin.cpp
        System.cpp
)