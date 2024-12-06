cmake_minimum_required(VERSION 3.29)
project(lab_1)

set(CMAKE_CXX_STANDARD 20)

include_directories(OpenGL/glad/include)

include_directories(OpenGL/glew-2.1.0/include)
link_directories(OpenGL/glew-2.1.0/lib/Release/x64)

include_directories(OpenGL/glfw-3.4.bin.WIN64/include)
link_directories(OpenGL/glfw-3.4.bin.WIN64/lib-mingw-w64)

add_executable(lab_1 main.cpp
        Figure.cpp
        Box.cpp)

add_library(glad OpenGL/glad/src/glad.c)
target_link_libraries(lab_1 glad)

target_link_libraries(lab_1
        glfw3
        GLEW32
        opengl32
        winmm
        gdi32
)