#pragma once
//#include <unordered_map>
#include <vector>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include "Meshes.h"

using GLuint = unsigned int;
struct GLFWwindow;

namespace sge
{
	class InstanceRenderer
	{
		using vao_id = GLuint;
		using transf_id = GLuint;

	public:
		explicit InstanceRenderer(GLFWwindow* window);
		void set_world_to_view(const glm::mat4& camera) const;
		static void render(const MeshSkeleton& mesh, std::vector<glm::mat4>& meshInstances, const float& interp);

	private:
		static char* transformBufferOffset(int i);
		void setProgramID(GLuint programID);
		GLuint programID;
		GLuint cameraUniformID;
		GLFWwindow* window;
	};
}
