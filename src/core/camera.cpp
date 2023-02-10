#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

// TODO(ellora): still as static values?
static float near = 0.1f;
static float far = 100.f;
static glm::vec3 up = { 0.f, 1.0f, 0.f };

glm::mat4 Camera::get_view()
{
	return glm::lookAt(position, orientation, up);
}

glm::mat4 Camera::get_proj()
{
	// TODO(ellora): find a way to get aspect ratio from scren
	return glm::perspective(glm::radians(fov), 1.f, near, far);
}
