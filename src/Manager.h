#pragma once
#include <unordered_map>
#include <vector>
#include <memory>

#include <GL/glew.h>

#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_SWIZZLE


#include "InstanceRenderer.h"
#include "InputState.h"
#include "Body.h"
#include "Camera.h"

//TODO make map or vector of transforms, make datatype with transforms and
//TODO normal transforms, (later: materials, etc.)
namespace sge
{
	class Manager
	{
		using vao_id = GLuint;
		using Renderable = std::pair<vao_id, glm::mat4>;
	public:
		explicit Manager(GLFWwindow* window);
		void update(const float& dt);
		void render(const float& interp);
		
	private:
		std::unique_ptr<InstanceRenderer> renderer;

		Camera camera;
		Body player;
		std::vector<Body> bodies;
		std::vector<MeshSkeleton> meshes;
		std::unordered_map<vao_id, std::vector<glm::mat4>> meshInstances;
		std::vector<Renderable> renderables;

		GLFWwindow* window;
	};
}