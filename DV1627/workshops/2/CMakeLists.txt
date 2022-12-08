cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project(Minigolf VERSION 0.1.0)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fno-optimize-sibling-calls")
file(GLOB SOURCES
    includes/*.hpp
    src/ResultColumn.cpp
    src/Protocol.cpp
)

add_executable(Minigolf src/main.cpp)
add_executable(Test1 test/TestResultColumn.cpp)
add_executable(Test2 test/TestProtocol.cpp)

add_library(Libs ${SOURCES})

target_link_libraries(Minigolf Libs)
target_link_libraries(Test1 Libs)
target_link_libraries(Test2 Libs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
