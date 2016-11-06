#include "Engine.h"
#include "InputState.h"
#include <iostream>


namespace sge
{
	void Engine::start() const
	{
		static const auto hz{ 60 };
		static auto constexpr dt{ 1.f / hz };
		auto frames = 0;
		auto updates = 0;
		auto updateMissed = 0;

		//TODO: use chrono
		double frameStart, frameEnd, frameTime;

		double dtAccumulated = 0;
		double secondsPassed = 0;

		auto isRunning = true;
		while (isRunning)
		{
			frameStart = glfwGetTime();

			if (dtAccumulated > 3 * dt)
			{
				dtAccumulated = 2 * dt;
				updateMissed++;
			}

			while (dtAccumulated > dt)
			{
				glfwPollEvents();
				isRunning = !input_state::q_pressed() && !input_state::esc_pressed();

				manager->update(dt);
				dtAccumulated -= dt;

				updates++;
			}

			const auto& interp = static_cast<float>(dtAccumulated / dt);

			if (interp > 0)
			{
				manager->render(interp);
				frames++;
			}

			if (secondsPassed > 1.0)
			{
				std::cout << " FPS: " << frames << " UPS: " << updates << " Update overflows: " << updateMissed << std::endl;
				//printDebugInfo();
				secondsPassed -= 1.0;
				frames = 0;
				updates = 0;
			}

			frameEnd = glfwGetTime();

			frameTime = (frameEnd - frameStart);

			dtAccumulated += frameTime;
			secondsPassed += frameTime;
		}
	}


	Engine::Engine()
	{
		initGlfw();

		initWindowed(1024, 768); //initFullscreen();
		
		glfwMakeContextCurrent(window);
		glfwSwapInterval(0);
		//glfwSwapInterval(1); //vsync

		input_state::initCallbacks(window);
		
		initGlew();
		
		initGl();
		manager = std::make_unique<Manager>(Manager{ window });
	}

	void Engine::initFullscreen()
	{
		auto monitor = glfwGetPrimaryMonitor();
		auto mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		window = glfwCreateWindow(mode->width, mode->height, "Game Engine Prototype", monitor, nullptr);
	}

	void Engine::initWindowed(int width, int height)
	{
		window = glfwCreateWindow(width, height, "Game Engine Prototype", nullptr, nullptr);

		if (!window)
			throw std::runtime_error("Failed to create window.");

		std::cout << "Window created." << std::endl;
	}

	void Engine::initGlfw()
	{
		if (glfwInit() != GL_TRUE)
			throw std::runtime_error("GLFW failed to initialise.");

		std::cout << "GLFW initialized." << std::endl;
	}

	void Engine::initGlew()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("GLEW failed to initialise.");

		else
			std::cout << "GLEW initialized." << std::endl;
	}

	void Engine::initGl() const
	{
		glClearColor(0.2f, 0.1f, 0.2f, 1);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glfwSwapBuffers(window);
		glfwShowWindow(window);
	}

	Engine::~Engine()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}
