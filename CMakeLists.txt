cmake_minimum_required(VERSION 3.0)

set(PROJECT starlight)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(lib OpenGL32)

project(${PROJECT})

# GLFW
add_subdirectory(lib/glfw)
set(GLFW_INCLUDE lib/glfw/include)
list(APPEND lib glfw)

# GLAD
add_library(glad lib/glad/src/glad.c)
set(GLAD_INCLUDE lib/glad/include)
target_include_directories(glad PRIVATE ${GLAD_INCLUDE})
list(APPEND lib glad)

# DearImgui
set(IMGUI_INCLUDE lib/imgui/ lib/imgui/backends)
add_library(imgui
	lib/imgui/imgui.cpp
	lib/imgui/imgui_demo.cpp
	lib/imgui/imgui_draw.cpp
	lib/imgui/imgui_tables.cpp
	lib/imgui/imgui_widgets.cpp
	lib/imgui/backends/imgui_impl_opengl3.cpp
	lib/imgui/backends/imgui_impl_glfw.cpp)
target_include_directories(imgui PRIVATE ${GLFW_INCLUDE} ${IMGUI_INCLUDE})
target_link_libraries(imgui glfw)
list(APPEND lib imgui)

# STB
set(STB_INCLUDE lib/stb)

# GLM
set(GLM_INCLUDE lib/glm)

# program
add_executable(
	${PROJECT}
	src/gfx/shader.cpp
	src/gfx/texture.cpp
	src/main.cpp)
target_link_libraries(${PROJECT} ${lib})
target_include_directories(
	${PROJECT} PRIVATE
	${IMGUI_INCLUDE}
	${STB_INCLUDE}
	${GLM_INCLUDE}
	${GLAD_INCLUDE}
	${GLFW_INCLUDE})