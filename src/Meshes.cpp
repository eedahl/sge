#include "Meshes.h"

namespace sge
{
	namespace meshes
	{
		//std::vector<MeshSkeleton> MeshLoader::meshes{};


		GLuint init_transform_buffer()
		{
			GLuint transformBufferId{ 0 };
			glGenBuffers(1, &transformBufferId);

			static auto constexpr TransformLocation{ 3 };
			for (auto i = TransformLocation; i < TransformLocation + 4; i++)
			{
				glEnableVertexAttribArray(i);
				glVertexAttribDivisor(i, 1);
			}
			return transformBufferId;
		}

		//position, normal, tangent and bitangent
		//diffuse color, specular color, texture coords
		//skinning weights

		Mesh make_mesh(std::vector<VertexBuffer> &vbos, std::vector<GLushort> &indices)
		{
			GLuint id{ 0 };
			glGenVertexArrays(1, &id);
			glBindVertexArray(id);

			GLuint byteSize{ 0 };
			for (auto & vbo : vbos)
				byteSize += vbo.sizeOf();

			GLuint vertexBufferID{ 0 };
			glGenBuffers(1, &vertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, byteSize, nullptr, GL_DYNAMIC_DRAW);

			auto location = 0;
			GLintptr offset = 0;
			for (auto &vbo : vbos)
			{
				if (location > 0)
				{
					auto pvbo = vbos.at(location - 1);
					offset += pvbo.sizeOf();
				}

				glEnableVertexAttribArray(location);
				glVertexAttribPointer(location, vbo.rank, GL_FLOAT, GL_FALSE, 0, static_cast<const char*>(nullptr) + offset);
				glBufferSubData(GL_ARRAY_BUFFER, offset, vbo.sizeOf(), vbo.buffer.data());
				location++;
			}

			auto indexCount = static_cast<GLuint>(indices.size());

			GLuint indexBufferID{ 0 };
			glGenBuffers(1, &indexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GL_UNSIGNED_SHORT), indices.data(), GL_STATIC_DRAW);

			auto transformBufferId = init_transform_buffer();

			glBindVertexArray(0);

			return Mesh{ vbos, indices };
		}

		MeshSkeleton make_mesh_skeleton(std::vector<VertexBuffer> &vbos, std::vector<GLushort> &indices)
		{
			GLuint id{ 0 };
			glGenVertexArrays(1, &id);
			glBindVertexArray(id);

			GLuint byteSize{ 0 };
			for (auto & vbo : vbos)
				byteSize += vbo.sizeOf();

			GLuint vertexBufferID{ 0 };
			glGenBuffers(1, &vertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, byteSize, nullptr, GL_DYNAMIC_DRAW);

			auto location = 0;
			GLintptr offset = 0;
			for (auto &vbo : vbos)
			{
				if (location > 0)
				{
					auto pvbo = vbos.at(location - 1);
					offset += pvbo.sizeOf();
				}

				glEnableVertexAttribArray(location);
				glVertexAttribPointer(location, vbo.rank, GL_FLOAT, GL_FALSE, 0, static_cast<const char*>(nullptr) + offset);
				glBufferSubData(GL_ARRAY_BUFFER, offset, vbo.sizeOf(), vbo.buffer.data());
				location++;
			}

			auto indexCount = static_cast<GLuint>(indices.size());

			GLuint indexBufferID{ 0 };
			glGenBuffers(1, &indexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GL_UNSIGNED_SHORT), indices.data(), GL_STATIC_DRAW);

			auto transformBufferId = init_transform_buffer();

			glBindVertexArray(0);

			return MeshSkeleton{ size_t{ id }, indexCount, transformBufferId };
		}


		namespace test_meshes
		{
			MeshSkeleton triangle()
			{
				std::vector<float> pos
				{
					-0.5f, -0.5f,
					0.5f, -0.5f,
					0.0f, 0.5f
				};

				std::vector<float> norm
				{
					.0f, .0f, +1.0f,
					.0f, .0f, +1.0f,
					.0f, .0f, +1.0f,
					.0f, .0f, +1.0f
				};

				std::vector<float> col
				{
					1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f
				};

				std::vector<GLushort> indices{ 0, 1, 2 };

				VertexBuffer positions{ pos, 2 };
				VertexBuffer normals{ norm, 3 };
				VertexBuffer colours{ col , 3 };

				std::vector<VertexBuffer> vbo{ positions, normals, colours };

				return make_mesh_skeleton(vbo, indices);
			}

			MeshSkeleton square()
			{
				std::vector<float> pos
				{
					-0.5f, -0.5f,
					0.5f, -0.5f,
					0.5f, 0.5f,
					-0.5f, 0.5f
				};

				VertexBuffer positions{ pos, 2 };

				std::vector<float> norm
				{
					.0f, .0f, +1.0f,
					.0f, .0f, +1.0f,
					.0f, .0f, +1.0f,
					.0f, .0f, +1.0f
				};

				VertexBuffer normals{ norm, 3 };

				std::vector<float> col
				{
					1.f, 0.f, .4f,
					1.f, 0.f, .4f,
					1.f, 0.f, .4f,
					1.f, 0.f, .4f
				};

				VertexBuffer colours{ col , 3 };

				std::vector<GLushort> indices
				{
					0, 1, 2, 0, 2, 3,
				};

				std::vector<VertexBuffer> vbo{ positions, normals, colours };

				return make_mesh_skeleton(vbo, indices);
			}

			MeshSkeleton sheep()
			{
				std::vector<float> pos
				{
					//top verts
					-0.1f, +0.1f, +0.1f,
					+0.1f, +0.1f, +0.1f,
					+0.1f, -0.1f, +0.1f,
					-0.1f, -0.1f, +0.1f
					//bottom verts
					-0.1f, +0.1f, -0.1f,
					+0.1f, +0.1f, -0.1f,
					+0.1f, -0.1f, -0.1f,
					-0.1f, -0.1f, -0.1f
				};

				VertexBuffer positions{ pos, 3 };

				std::vector<GLushort> indices
				{
					0, 1, 2, 0, 2, 3, //top
					4, 6, 5, 4, 7, 6, //bottom
					4, 5, 1, 4, 1, 0, //front

					7, 2, 6, 7, 3, 2, //back
					5, 6, 6, 5, 2, 1, //rhs
					4, 3, 0, 4, 0, 7 //lhs
				};

				auto x = std::sqrtf(1.0f / 3.0f);
				std::vector<float> norm
				{
					//top
					-x, +x, +x,
					+x, +x, +x,
					+x, -x, +x,
					-x, -x, +x,
					//bottom
					-x, +x, -x,
					+x, +x, -x,
					+x, -x, -x,
					-x, -x, -x
				};

				VertexBuffer normals{ norm, 3 };

				std::vector<float> col
				{
					1.f, 0.f, 0.f,
					1.f, 0.f, 0.f,
					1.f, 0.f, 0.f,
					1.f, 0.f, 0.f,
					0.f, 0.f, 1.f,
					0.f, 0.f, 1.f,
					0.f, 0.f, 1.f,
					0.f, 0.f, 1.f
				};

				VertexBuffer colours{ col , 3 };

				std::vector<VertexBuffer> vbo{ positions, normals, colours };

				return make_mesh_skeleton(vbo, indices);
			}
		}
	}
}