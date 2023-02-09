#include "shader.hpp"

#include <iostream>
#include <glad/glad.h>

void Shader::compile(const char *vs_src, const char *fs_src)
{
	compile_shader(vs_id, GL_VERTEX_SHADER, vs_src);
	compile_shader(fs_id, GL_FRAGMENT_SHADER, fs_src);

	id = glCreateProgram();
	glAttachShader(id, vs_id);
	glAttachShader(id, fs_id);
	glLinkProgram(id);

	{
		int32_t status;
		uint8_t info_log[1 << 9];

		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if(!status) {
			glGetProgramInfoLog(id, 512, NULL, (GLchar*)info_log);
			std::cout << "Link program error: " << info_log << std::endl;
		}
	}
}

void Shader::compile_shader(uint32_t &id, uint32_t s_type, const char *src)
{
	id = glCreateShader(s_type);
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	{
		int32_t status;
		uint8_t info_log[1 << 9];

		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		if(!status) {
			glGetShaderInfoLog(id, 512, NULL, (GLchar*)info_log);
			std::cout << "Compile shader error: " << info_log << std::endl;
		}
	}
}

void Shader::unload()
{
	glDeleteProgram(id);
}

void Shader::send_mat4(const char* name, glm::mat4x4 mat)
{
	glUseProgram(id);
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}