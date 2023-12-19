cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

# If you are working in Linux and want to check for memory leaks,
# uncomment this line:
# set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fno-optimize-sibling-calls")

project ("assignment2-connect-n")

# Add source to this project's executable.
add_executable(application
    "main.cpp"
    "src/ConnectN.cpp"
    # "src/Visualizer.cpp"
)
target_include_directories(application PRIVATE "include")


add_executable(auto-tests
	"test/test-main.cpp"
    "src/ConnectN.cpp"
    "src/Visualizer.cpp"
)
target_include_directories(auto-tests PRIVATE "include" "test/include")
