#pragma once
#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/detail/type_vec2.hpp>


using glm::vec2;
struct GLFWwindow;

namespace sge
{
	namespace input_state
	{
		static std::array<int, GLFW_KEY_LAST> keyStates{};
		static glm::vec2 mousePosition{};

		void initCallbacks(GLFWwindow *window);
		void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
		void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

		glm::vec2 mouse_pos();
		int w_pressed();
		int s_pressed();
		int a_pressed();
		int d_pressed();
		int q_pressed();
		int up_pressed();
		int down_pressed();
		int left_pressed();
		int right_pressed();
		int esc_pressed();
		int space_pressed();
	};
}