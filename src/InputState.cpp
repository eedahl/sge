#include "InputState.h"
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>
#include <iostream>

static constexpr auto windowWidth{ 1024 };
static constexpr auto windowHeight{ 768 };

namespace sge
{
	namespace input_state
	{
		glm::vec2 mouse_pos() { return mousePosition; }
		int w_pressed() { return keyStates[GLFW_KEY_W]; }
		int s_pressed() { return keyStates[GLFW_KEY_S]; }
		int a_pressed() { return keyStates[GLFW_KEY_A]; }
		int d_pressed() { return keyStates[GLFW_KEY_D]; }
		int q_pressed() { return keyStates[GLFW_KEY_Q]; }
		int up_pressed() { return keyStates[GLFW_KEY_UP]; }
		int down_pressed() { return keyStates[GLFW_KEY_DOWN]; }
		int left_pressed() { return keyStates[GLFW_KEY_LEFT]; }
		int right_pressed() { return keyStates[GLFW_KEY_RIGHT]; }
		int esc_pressed() { return keyStates[GLFW_KEY_ESCAPE]; }
		int space_pressed() { return keyStates[GLFW_KEY_SPACE]; }

		void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			input_state::keyStates[key] = action;
		}

		void cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
		{
			input_state::mousePosition = glm::vec2(2 * xpos / windowWidth - 1, -2 * ypos / windowHeight + 1);
		}

		void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			{
			}

			if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
			{
			}

			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
			{
			}

			if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
			{
			}
		}

		void initCallbacks(GLFWwindow *window)
		{
			glfwSetKeyCallback(window, keyCallback);
			glfwSetCursorPosCallback(window, cursorPosCallback);
			glfwSetMouseButtonCallback(window, mouseButtonCallback);
		}
	}
}