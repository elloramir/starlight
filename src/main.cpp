#include "gfx/shader.hpp"
#include "gfx/texture.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <inttypes.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(void)
{
	GLFWwindow* window;

	int32_t screen_width = 600;
	int32_t screen_height = 600;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(screen_width, screen_height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	std::cout << "OpenGL loaded" << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;

	// dear imgui
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.WantSaveIniSettings = true;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}


	Shader shader;
	shader.compile(
		"#version 330\n"
		"layout(location=0) in vec3 a_position;"
		"layout(location=1) in vec2 a_uv;"
		"out vec2 v_uv;"
		"uniform mat4 i_model;"
		"uniform mat4 i_view;"
		"uniform mat4 i_proj;"
		"void main() {"
		"v_uv = a_uv.xy;"
		"gl_Position = i_proj * i_view * i_model * vec4(a_position.xyz, 1.0);"
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
	tex.load_from_file("res/cat.jpg");

	uint32_t vao, vbo, ebo;

	float vertices[] = {
		//  0.5f,  0.5f, 0.5f,  1.f, 0.f, // top right
		//  0.5f, -0.5f, 0.5f,  1.f, 1.f, // bottom right
		// -0.5f, -0.5f, 0.5f,  0.f, 1.f, // bottom left
		// -0.5f,  0.5f, 0.5f,  0.f, 0.f, // top left 

		//  0.5f,  0.5f, -0.5f,  0.f, 0.f, // top right
		//  0.5f, -0.5f, -0.5f,  0.f, 1.f, // bottom right
		// -0.5f, -0.5f, -0.5f,  1.f, 1.f, // bottom left
		// -0.5f,  0.5f, -0.5f,  1.f, 0.f, // top left

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	uint32_t indices[] = {
		0, 1, 3,
		1, 2, 3,

		4, 5, 7,
		5, 6, 7,

		0, 3, 4,
		3, 7, 4,

		1, 5, 2,
		5, 6, 2,

		0, 4, 1,
		4, 5, 1,

		3, 2, 7,
		2, 6, 7
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

	// camera stuff
	auto view = glm::mat4(1.0f);
	auto model = glm::mat4(1.0f);
	auto view_trans = glm::vec3(0.f, 0.f, -2.8f);
	glm::mat4 projection;
	float cam_degs = 0.f;
	float perspective_fov = 45.f;


	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SliderFloat("model - rotate", &cam_degs, 0.0f, 360.0f, "degs: %.1f");
		ImGui::SliderFloat("perspective - fov", &perspective_fov, 0.0f, 360.0f, "degs: %.1f");
		ImGui::SliderFloat3("view - trans", &view_trans[0], -10.0f, 10.0f, "%.1f");

		// update game
		model = glm::rotate(glm::mat4(1), glm::radians(cam_degs), glm::vec3(1.0f, 1.0f, 0.0f));
		view = glm::translate(glm::mat4(1), view_trans); 
		projection = glm::perspective(glm::radians(perspective_fov), (float)screen_width / (float)screen_height, 0.1f, 100.0f);

		shader.send_mat4("i_model", model);
		shader.send_mat4("i_view", view);
		shader.send_mat4("i_proj",projection);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, screen_width, screen_height);
		glClearColor(0.3f, 0.1f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader.id);
		// glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}