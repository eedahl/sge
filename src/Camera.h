#pragma once

#include "InputState.h"
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>

using glm::vec3;
using glm::mat4;


namespace sge
{
	class Camera
	{
	public:
		explicit Camera(float aspect_ratio)
			: position(glm::vec3{ 0.f, -2.f, 2.f }),
			viewDirection(glm::normalize(glm::vec3{ 0.f, 1.f, -1.f })),
			up(glm::normalize(glm::vec3{ 0.f, 1.f, 1.f })),
			fov(75.f), near(0.01f), far(1000.f),
			aspect_ratio(aspect_ratio){ }

		glm::mat4 world_to_view() const;
		void handleInput();

	private:
		glm::vec3 position;
		glm::vec3 viewDirection;
		glm::vec3 up;
		float fov;
		float near;
		float far;
		float aspect_ratio;
	};
}