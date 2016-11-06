#pragma once
#include <glm/vec2.hpp>

namespace sge {
	namespace force {
		namespace unit {
			static const glm::vec3 forward{ 0.f,  1.f, 0 };
			static const glm::vec3 back{ 0.f, -1.f, 0 };
			static const glm::vec3 left{ -1.f,  0.f, 0 };
			static const glm::vec3 right{ 1.f,  0.f, 0 };

			static const float clockwise{ -1.f };
			static const float anti_clockwise{ 1.f };
		}
	}
}



