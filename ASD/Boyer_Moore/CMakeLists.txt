cmake_minimum_required(VERSION 3.23)
project(Boyer_Moore)

set(SOURCES
        Boyer_Moore.cpp
        Boyer_Moore.h
)
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})
message(${SOURCES})