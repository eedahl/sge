#include "BatchRenderer.h"
#include <iostream>
#include <memory>
#include <map>
#include <GL/glew.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

static auto constexpr Mat4ComponentCount{ 16 };
static auto constexpr TransformLocation{ 3 };

namespace sge
{
	BatchRenderer::BatchRenderer(GLFWwindow* window)
		: window(window)
	{
		auto program = Program("../basicVertexShader.glsl", "../basicFragmentShader.glsl");
		program.init();
		program.use();
		programID = program.getID();
		//renderables{};
		cameraUniformID = glGetUniformLocation(programID, "camera");
	}

	void BatchRenderer::set_world_to_view(const glm::mat4& camera) const
	{
		static auto const NumberOfMatrices{ 1 };
		glUniformMatrix4fv(cameraUniformID, NumberOfMatrices, GL_FALSE, &camera[0][0]);
	}

	char* BatchRenderer::transformBufferOffset(int i)
	{
		return static_cast<char*>(nullptr) + (sizeof(glm::vec4) * (i - TransformLocation));
	}



	void BatchRenderer::render(const float& interp)
	{
#if 0
		for (const auto &renderable : renderables)
		{
			const auto id = renderable.vao_id();
			glBindVertexArray(id);

			glBindBuffer(GL_ARRAY_BUFFER, mesh.transformBufferId);

			auto transformBuffer = static_cast<void*>(meshInstances.data());
			auto transformBufferSize = meshInstances.size() * Mat4ComponentCount * sizeof(float);
			glBufferData(GL_ARRAY_BUFFER, transformBufferSize, transformBuffer, GL_DYNAMIC_DRAW);

			for (auto i = TransformLocation; i < TransformLocation + 4; i++)
			{
				glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), transformBufferOffset(i));
			}

			auto instanceCount = static_cast<GLuint>(meshInstances.size());
			glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_SHORT, nullptr);

			glBindVertexArray(0);
#endif
		}
	}

	void BatchRenderer::submit_renderable(Renderable r)
	{
		renderables.emplace_back(r);
	}

	void BatchRenderer::sort_renderables()
	{
		std::sort(renderables.begin(), renderables.end(), [](Renderable r1, Renderable r2) {return r1.vao_id() < r2.vao_id();});
	}

	void BatchRenderer::setProgramID(GLuint programID)
	{
		this->programID = programID;
	}
}