cmake_minimum_required(VERSION 3.12)
project(compiler CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set debug build by default for development
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Enable debug symbols and disable optimizations for Debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0")

# Find required packages
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Find dot executable
find_program(DOT_EXECUTABLE dot)
if(NOT DOT_EXECUTABLE)
    message(WARNING "dot not found - PDF generation targets will not be available")
endif()

# Set output directories for generated files
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

# Generate lexer and parser with debug info
BISON_TARGET(Parser
        ${CMAKE_CURRENT_SOURCE_DIR}/parser.yy
        ${GENERATED_DIR}/parser.tab.cc
        COMPILE_FLAGS "-t -v"
        DEFINES_FILE ${GENERATED_DIR}/parser.tab.hh
)

FLEX_TARGET(Scanner
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer.flex
        ${GENERATED_DIR}/lex.yy.c
        COMPILE_FLAGS "-d"
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

# Set source files (excluding header files)
set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
)

# Add compiler executable
add_executable(compiler ${SOURCE_FILES})

# Add compile options, but keep debug info
target_compile_options(compiler PRIVATE
        -w                  # Suppress warnings
        -g3                 # Maximum debug info
        -fno-omit-frame-pointer  # Keep frame pointer for better debugging
)

# Include directories for generated files
target_include_directories(compiler PRIVATE
        ${GENERATED_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set flex-specific compile definitions
target_compile_definitions(compiler PRIVATE
        YY_NO_UNISTD_H=1
        YY_FLEX_SUBMINOR_VERSION=2
)

# Ensure lex.yy.c is compiled as C++
set_source_files_properties(
        ${FLEX_Scanner_OUTPUTS}
        PROPERTIES
        LANGUAGE CXX
        COMPILE_FLAGS "-g3 -O0"  # Ensure debug symbols for generated files
)

# Set source file properties for better debugging
set_source_files_properties(
        ${SOURCE_FILES}
        PROPERTIES
        COMPILE_FLAGS "-g3 -O0"
)

# Custom targets for PDF generation (only if dot is available)
if(DOT_EXECUTABLE)
    add_custom_target(tree
            COMMAND ${DOT_EXECUTABLE} -Tpdf ${CMAKE_CURRENT_BINARY_DIR}/tree.dot -o${CMAKE_CURRENT_BINARY_DIR}/tree.pdf
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/tree.dot
            COMMENT "Generating tree PDF"
    )

    add_custom_target(st
            COMMAND ${DOT_EXECUTABLE} -Tpdf ${CMAKE_CURRENT_BINARY_DIR}/symbol_table.dot -o${CMAKE_CURRENT_BINARY_DIR}/symbol_table.pdf
            COMMAND chmod 777 ${CMAKE_CURRENT_BINARY_DIR}/symbol_table.dot
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/symbol_table.dot
            COMMENT "Generating symbol table PDF"
    )
endif()

# Custom target to generate parser debug output
add_custom_target(parser_debug
        COMMAND YYDEBUG=1 ./compiler
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS compiler
)

# Clean target
add_custom_target(cleanall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_clean.cmake
)

# Generate cleaning script
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/cmake_clean.cmake
        "
file(REMOVE_RECURSE
    ${GENERATED_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/tree.dot
    ${CMAKE_CURRENT_BINARY_DIR}/tree.pdf
    ${CMAKE_CURRENT_BINARY_DIR}/symbol_table.dot
    ${CMAKE_CURRENT_BINARY_DIR}/symbol_table.pdf
    ${CMAKE_CURRENT_BINARY_DIR}/compiler.dSYM
)
")