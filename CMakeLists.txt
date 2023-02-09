cmake_minimum_required(VERSION 3.0)

set(PROJECT starlight)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(libs opengl32)

project(${PROJECT})

# GLFW
add_subdirectory(libs/glfw)
set(GLFW_INCLUDE libs/glfw/include)
list(APPEND libs glfw)

# GLAD
add_library(glad libs/glad/src/glad.c)
set(GLAD_INCLUDE libs/glad/include)
target_include_directories(glad PRIVATE ${GLAD_INCLUDE})
list(APPEND libs glad)

# DearImgui
set(IMGUI_INCLUDE libs/imgui/ libs/imgui/backends)
add_library(imgui
	libs/imgui/imgui.cpp
	libs/imgui/imgui_demo.cpp
	libs/imgui/imgui_draw.cpp
	libs/imgui/imgui_tables.cpp
	libs/imgui/imgui_widgets.cpp
	libs/imgui/backends/imgui_impl_opengl3.cpp
	libs/imgui/backends/imgui_impl_glfw.cpp)
target_include_directories(imgui PRIVATE ${GLFW_INCLUDE} ${IMGUI_INCLUDE})
target_link_libraries(imgui glfw)
list(APPEND libs imgui)

# STB
set(STB_INCLUDE libs/stb)

# GLM
set(GLM_INCLUDE libs/glm)

# program
add_executable(
	${PROJECT}
	src/gfx/shader.cpp
	src/gfx/texture.cpp
	src/main.cpp)
target_link_libraries(${PROJECT} ${libs})
target_include_directories(
	${PROJECT} PRIVATE
	${IMGUI_INCLUDE}
	${STB_INCLUDE}
	${GLM_INCLUDE}
	${GLAD_INCLUDE}
	${GLFW_INCLUDE})