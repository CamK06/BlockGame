cmake_minimum_required(VERSION 3.2)
project(blockgame)

file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp" "src/**/**/*.cpp")

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(blockgame ${SOURCES})
target_link_libraries(blockgame glfw GLEW::GLEW OpenGL::GL freetype pthread)
# TODO: Make this cross-platform
target_include_directories(blockgame PUBLIC "/usr/include/freetype2")