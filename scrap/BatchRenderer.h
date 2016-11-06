#pragma once
//#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include "Meshes.h"
#include "Program.h"

using GLuint = unsigned int;
struct GLFWwindow;

namespace sge
{
	struct Renderable
	{
		MeshSkeleton m;
		glm::mat4 w;

		inline GLuint vao_id() const { return m.vaoId; }
	};

	class BatchRenderer
	{
		using vao_id = GLuint;
		using transf_id = GLuint;

	public:
		explicit BatchRenderer(GLFWwindow* window);
		void set_world_to_view(const glm::mat4& camera) const;
		void render(const float& interp);
		void submit_renderable(Renderable r);
		void sort_renderables();

	private:
		static char* transformBufferOffset(int i);
		void setProgramID(GLuint programID);
		GLFWwindow* window;
		GLuint programID;
		GLuint cameraUniformID;
		//std::vector<Renderable> renderables;
	};
}
