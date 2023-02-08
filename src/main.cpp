#include "gfx/shader.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <inttypes.h>

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	std::cout << "OpenGL loaded" << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;

	Shader shader;
	shader.compile(
		"#version 330\n"
		"layout(location=0) in vec3 a_position;"
		"void main() {"
		"gl_Position = vec4(a_position.xyz, 1.0);"
		"}",

		"#version 330\n"
		"out vec4 v_color;"
		"void main() {"
		"v_color = vec4(1.0, 0.4, 0.2, 1.0);"
		"}"
	);

	uint32_t vao, vbo, ebo;

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	uint32_t indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3, // second triangle
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3f, 0.1f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader.id);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}