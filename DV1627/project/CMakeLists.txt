cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

# If you are working in Linux and want to check for memory leaks,
# uncomment this line:
# set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fno-optimize-sibling-calls")

project ("snake-project")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# List all your source files that is needed to
# compile the application
add_executable(application
    "main.cpp"
    "src/Game.cpp"
    "src/GameEntity.cpp"
    "src/SnakeHead.cpp"
    "src/SnakeBody.cpp"
    # Maybe this?
    #"src/game.cpp"
    #"src/menu.cpp"
)

# List all include files
target_include_directories(application PRIVATE
    "."
    "include"
    "src"
)

target_link_libraries(application ${CURSES_LIBRARIES})
