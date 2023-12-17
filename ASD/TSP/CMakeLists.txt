cmake_minimum_required(VERSION 3.23)

project(TSP)

set(SOURCES
        Task_tsp.cpp
)
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})
message(${SOURCES})