cmake_minimum_required(VERSION 3.26)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

# Set the path to Raylib directory
set(RAYLIB_DIR "D:/MSYS2/mingw64")

# Find Raylib and include its directories
find_package(raylib REQUIRED PATHS ${RAYLIB_DIR}/lib/cmake/raylib/)
include_directories(${RAYLIB_DIR}/include)

# Add your source files
add_executable(untitled1
        main.cpp
        ball.cpp
        player.cpp
        game.cpp)

# Link Raylib library to your project
target_link_libraries(untitled1 raylib)
