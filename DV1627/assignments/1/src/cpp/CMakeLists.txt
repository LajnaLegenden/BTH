# CMakeList.txt : CMake project for a1-assembler, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "CMAKE_GENERATOR_INSTANCE: ${CMAKE_GENERATOR}")

project ("assignment1-assembler")

# Add source to this project's executable.
add_executable(application
    "main.cpp"
    "assembler.cpp"
)

#This will copy all the assembly-test-files to where the executable file is
add_custom_command(TARGET application POST_BUILD
	COMMAND $(CMAKE_COMMAND) -E copy "${PROJECT_SOURCE_DIR}/*.asm" "${PROJECT_SOURCE_DIR}/build/"
)

add_executable(auto-tests
	"test/test-main.cpp"
	"assembler.cpp"
)
target_include_directories(auto-tests PRIVATE ".")

# This will copy an assembly-file used in testing to where the executable file is
add_custom_command(TARGET auto-tests POST_BUILD
	COMMAND $(CMAKE_COMMAND) -E copy "${PROJECT_SOURCE_DIR}/test/*.asm" "${PROJECT_SOURCE_DIR}/build/test/test.asm"
)
