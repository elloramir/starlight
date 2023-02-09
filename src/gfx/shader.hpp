#pragma once

#include <glm/glm.hpp>
#include <inttypes.h>

class Shader
{
public:
	uint32_t id;

	void compile(const char *vs_src, const char *fs_src);
	void unload();

	void send_mat4(const char* name, glm::mat4x4 mat);

private:
	uint32_t vs_id, fs_id; // TODO(elloramir): hot reloader

	void compile_shader(uint32_t &id, uint32_t s_type, const char *src);
};