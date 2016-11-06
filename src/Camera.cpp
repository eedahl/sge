#include "Camera.h"

namespace sge
{
	glm::mat4 Camera::world_to_view() const
	{
		return glm::perspective(fov, aspect_ratio, near, far) * glm::lookAt(position, 0.1f*glm::vec3(input_state::mouse_pos(), 0) + position + viewDirection, up);
	}

	void Camera::handleInput()
	{
		if (input_state::up_pressed())
			position.y += 0.01f;
		if (input_state::down_pressed())
			position.y -= 0.01f;

		if (input_state::left_pressed())
			position.x -= 0.01f;
		if (input_state::right_pressed())
			position.x += 0.01f;
	}
}