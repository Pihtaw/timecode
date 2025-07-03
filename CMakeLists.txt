cmake_minimum_required(VERSION 3.10)
project(timecodes)

set(SOURCE_FILES
    main.cpp
    time.cpp
    line.cpp
)

include_directories(include)

add_executable(timecodes ${SOURCE_FILES})