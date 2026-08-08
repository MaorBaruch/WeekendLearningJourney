cmake_minimum_required(VERSION 3.31)
project(LearningWindows)

set(CMAKE_CXX_STANDARD 20)

add_executable(LearningWindows main.cpp
        message_queue.cpp
        message_queue.h)
