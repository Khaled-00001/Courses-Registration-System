cmake_minimum_required(VERSION 3.20)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

<<<<<<< HEAD
add_executable(course_registration main.cpp Course.cpp)
=======
add_executable(course_regestiration main.cpp
        Course.cpp
        Course.h
        Student.cpp
        Student.h)
>>>>>>> 5c9df7e (adding courseRegisterationFunction)
