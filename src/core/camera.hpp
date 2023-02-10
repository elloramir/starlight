#pragma once

#include <glm/glm.hpp>

struct Camera
{
	glm::vec3 position { 0.f, 0.f, 0.f };
	glm::vec3 orientation = { 0.f, 0.f, 0.f };

	float fov = 45.f;

	glm::mat4 get_view();
	glm::mat4 get_proj();
};