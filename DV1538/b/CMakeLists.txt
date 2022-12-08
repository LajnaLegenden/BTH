cmake_minimum_required(VERSION 3.22)
#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fno-optimize-sibling-calls")
set(CMAKE_CXX_STANDARD 14)

project(b)
include_directories(.)

add_executable(b
        main.cpp BST.h)


add_executable(b_test
        test_file_of_bst_used_in_codegrade.cpp BST.h)
