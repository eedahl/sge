#pragma once
#include <vector>
#include <GL/glew.h>
#include "VertexBuffer.h"

namespace sge {

	struct MeshSkeleton
	{
		GLuint vaoId;
		GLuint indexCount;
		GLuint transformBufferId;
	};

	struct Mesh
	{
		std::vector<VertexBuffer> &vbos;
		std::vector<GLushort> &indices;
	};

	namespace meshes
	{
		namespace test_meshes
		{
			extern MeshSkeleton triangle();
			extern MeshSkeleton square();
			extern MeshSkeleton sheep();
		}

		//static auto getMeshes() { return MeshLoader::meshes; };
		//static void insertMesh(MeshSkeleton mesh) { meshes.emplace_back(mesh); }
		extern GLuint init_transform_buffer();
		extern Mesh make_mesh(std::vector<VertexBuffer> &vbos, std::vector<GLushort> &indices);
		extern MeshSkeleton make_mesh_skeleton(std::vector<VertexBuffer> &vbos, std::vector<GLushort> &indices);

		//std::vector<MeshSkeleton> meshes;
	};
}