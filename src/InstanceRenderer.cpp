#include "InstanceRenderer.h"
#include <iostream>
#include <memory>
#include <map>
#include <GL/glew.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderPipeline.h"

static auto constexpr Mat4ComponentCount{ 16 };
static auto constexpr TransformLocation{ 3 };

namespace sge
{
	InstanceRenderer::InstanceRenderer(GLFWwindow* window)
		: window(window)
	{
		auto program = Program("../res/basicVertexShader.glsl", "../res/basicFragmentShader.glsl");
		program.init();
		program.use();
		programID = program.getID();
		cameraUniformID = glGetUniformLocation(programID, "camera");
	}

	void InstanceRenderer::set_world_to_view(const glm::mat4& camera) const
	{
		static auto const NumberOfMatrices{ 1 };
		glUniformMatrix4fv(cameraUniformID, NumberOfMatrices, GL_FALSE, &camera[0][0]);
	}

	char* InstanceRenderer::transformBufferOffset(int i)
	{
		return static_cast<char*>(nullptr) + (sizeof(glm::vec4) * (i - TransformLocation));
	}

	void InstanceRenderer::render(const MeshSkeleton& mesh, std::vector<glm::mat4>& meshInstances, const float& interp)
	{
		glBindVertexArray(mesh.vaoId);

		glBindBuffer(GL_ARRAY_BUFFER, mesh.transformBufferId);

		auto transformBuffer = static_cast<void*>(meshInstances.data());
		auto transformBufferSize = meshInstances.size() * Mat4ComponentCount * sizeof(float);
		glBufferData(GL_ARRAY_BUFFER, transformBufferSize, transformBuffer, GL_DYNAMIC_DRAW);

		for (auto i = TransformLocation; i < TransformLocation + 4; i++)
		{
			glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), transformBufferOffset(i));
		}

		auto instanceCount = static_cast<GLuint>(meshInstances.size());
		glDrawElementsInstanced(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_SHORT, nullptr, instanceCount);
		glBindVertexArray(0);
	}

	void InstanceRenderer::setProgramID(GLuint programID)
	{
		this->programID = programID;
	}
}