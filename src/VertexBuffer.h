#pragma once
#include <GLFW/glfw3.h>

namespace sge {

	struct VertexBuffer
	{
		const std::vector<float> buffer;
		const GLuint rank;

		VertexBuffer(const std::vector<float>& buffer, GLuint rank)
			: buffer(buffer), rank(rank) {}

		GLuint sizeOf() const
		{
			return static_cast<GLuint>(buffer.size() * sizeof(float));
		}
	};
}