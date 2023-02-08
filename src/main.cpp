#include "gfx/shader.hpp"
#include "gfx/texture.hpp"

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
		"layout(location=1) in vec2 a_uv;"
		"out vec2 v_uv;"
		"void main() {"
		"v_uv = a_uv.xy;"
		"gl_Position = vec4(a_position.xyz, 1.0);"
		"}",

		"#version 330\n"
		"out vec4 v_color;"
		"in vec2 v_uv;"
		"uniform sampler2D v_tex;"
		"void main() {"
		"v_color = texture(v_tex, v_uv) * vec4(1.0, 1.0, 1.0, 1.0);"
		"}"
	);

	Texture tex;
	tex.load_from_file("cat.jpg");

	uint32_t vao, vbo, ebo;

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  1.f, 0.f, // top right
		 0.5f, -0.5f, 0.0f,  1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.0f,  0.f, 1.f, // bottom left
		-0.5f,  0.5f, 0.0f,  0.f, 0.f, // top left 
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, 640, 480);
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