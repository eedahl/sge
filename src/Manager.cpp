#include "Meshes.h"
#include "Manager.h"
#include "Physics.h"
#include "Utilities.h"
#include <iostream>

namespace sge
{
	Manager::Manager(GLFWwindow* window)
		: renderer{ std::make_unique<InstanceRenderer>(window) }, camera{util::aspect_ratio(window) }, player{ meshes::test_meshes::triangle() }, window{ window }
	{
		meshes.emplace_back(player.mesh);
		bodies.emplace_back(meshes::test_meshes::square());
	}

	void Manager::update(const float& dt)
	{
		//update camera
		camera.handleInput();
		renderer->set_world_to_view(camera.world_to_view());

		//reset particle states
		player.particle.accelleration = { 0, 0, 0 };
		player.particle.rotation = { 0, 0, 0 };

		physics::handle_player_input(player.particle);
		//get npc steering

		physics::step(player.particle, dt);

		//broad phase collision detection
		//narrow phase collision detection
		//solve_collisions(player, dt);

		//TODO: swap back and front transform buffer. clear front, add to front
		auto playerMeshVaoId = player.mesh.vaoId;
		meshInstances[playerMeshVaoId].clear();
		meshInstances[playerMeshVaoId].emplace_back(player.model_to_world());

		for (auto &body : bodies)
			meshInstances[body.mesh.vaoId].emplace_back(body.model_to_world());
	}

	void Manager::render(const float& interp)
	{
		//TODO: [&interp](current, previous){return instance.previous * interp + instance.current * (1.0f - interp);}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto &mesh : meshes)
			renderer->render(mesh, meshInstances[mesh.vaoId], interp);

		glfwSwapBuffers(window);
	}

	void printDebugInfo()
	{
		using std::cout; using std::endl;
	}
}