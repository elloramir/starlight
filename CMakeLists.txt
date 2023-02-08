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
	${STB_INCLUDE}
	${GLM_INCLUDE}
	${GLAD_INCLUDE}
	${GLFW_INCLUDE})