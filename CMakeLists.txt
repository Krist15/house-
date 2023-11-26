cmake_minimum_required(VERSION 3.27)

project(double-triangle VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(app ./src/main.cpp ./src/glad.c)

target_include_directories(app PRIVATE deps)

target_link_libraries(app /usr/local/Cellar/glfw/3.3.8/lib/libglfw.3.3.dylib OpenGL::GL)
