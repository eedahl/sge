#pragma once
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Manager.h"


namespace sge {

	class Engine
	{
	public:
		Engine();
		~Engine();
		void start() const;

	private:
		void initFullscreen();
		void initWindowed(int width, int height);
		static void initGlew();
		void initGl() const;
		static void initGlfw();

		GLFWwindow* window;
		std::unique_ptr<Manager> manager;
	};
}