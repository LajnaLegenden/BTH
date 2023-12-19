cmake_minimum_required(VERSION 3.16)
project(project)
include_directories(.)

add_executable(project
        main.cpp Graph.h)

add_executable(project_test
        GraphTest.cpp Graph.h)
