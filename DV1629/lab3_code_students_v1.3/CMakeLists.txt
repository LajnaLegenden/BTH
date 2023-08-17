cmake_minimum_required(VERSION 3.12)
project(FilesystemProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(filesystem
    main.cpp shell.cpp fs.cpp disk.cpp
)
add_executable(test1
    main.cpp test_script1.cpp fs.cpp disk.cpp
)

add_executable(test2
    main.cpp test_script2.cpp fs.cpp disk.cpp
)

add_executable(test3
    main.cpp test_script3.cpp fs.cpp disk.cpp
)

add_executable(test4
    main.cpp test_script4.cpp fs.cpp disk.cpp
)

add_executable(test5
    main.cpp test_script5.cpp fs.cpp disk.cpp
)

target_compile_definitions(test1 PRIVATE TEST_SCRIPT1)
target_compile_definitions(test2 PRIVATE TEST_SCRIPT2)
target_compile_definitions(test3 PRIVATE TEST_SCRIPT3)
target_compile_definitions(test4 PRIVATE TEST_SCRIPT4)
target_compile_definitions(test5 PRIVATE TEST_SCRIPT5)

add_custom_target(runtests
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test1
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test2
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test3
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test4
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test5
    DEPENDS test1 test2 test3 test4 test5
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_custom_target(clean-all
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_COMMAND} -E remove diskfile.bin
)

add_dependencies(runtests test1 test2 test3 test4 test5)

# Set the debug build type
set(CMAKE_BUILD_TYPE Debug)
