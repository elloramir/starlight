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
		io.IniFilename = "res/imgui.ini";
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
		"uniform vec4 light_color;"
		"uniform vec4 object_color;"
		"uniform sampler2D v_tex;"
		"void main() {"
		"float ambient_strength = 1.0;"
		"vec4 ambient = object_color * ambient_strength;"
		"vec4 result = ambient * object_color;"
		"v_color = texture(v_tex, v_uv) * result;"
		"}"
	);

	Texture tex;
	tex.load_from_file("res/cat.jpg");

	uint32_t vao, vbo;

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// rotation
		static float model_rot[3] = { 0 };
		ImGui::SliderFloat3("Rotation", model_rot, 0.f, 360.f, "%2.f");

		// light
		static glm::vec4 objec_color = { 1.f, 0.2f, 0.1f, 1.f };
		static glm::vec4 light_color = { 0.2f, 1.f, 0.3f, 1.f };
		ImGui::SliderFloat4("Object color", &objec_color[0], 0.f, 1.f);
		ImGui::SliderFloat4("Light color", &light_color[0], 0.f, 1.f);


		auto model = glm::mat4(1.f);
		model = glm::rotate(model, glm::radians(model_rot[0]), glm::vec3(1.f, 0.f, 0.f));
		model = glm::rotate(model, glm::radians(model_rot[1]), glm::vec3(0.f, 1.f, 0.f));
		model = glm::rotate(model, glm::radians(model_rot[2]), glm::vec3(0.f, 0.f, 1.f));

		shader.send_vec4("object_color", objec_color);
		shader.send_vec4("light_color", light_color);

		shader.send_mat4("i_model", model);
		shader.send_mat4("i_view", glm::mat4(1.f));
		shader.send_mat4("i_proj", glm::mat4(1.f));

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, screen_width, screen_height);
		glClearColor(0.3f, 0.1f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader.id);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}