#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>

#include "Meshes.h"
#include "Physics.h"

namespace sge
{
	struct Body
	{
		explicit Body(MeshSkeleton mesh) : mesh(mesh), hitbox{}, material{} {}

		auto model_to_world() const
		{
			return particle.placement;
		}

		MeshSkeleton mesh;
		physics::Particle particle;
		physics::collision::AABB hitbox;	//compute aabb, mass
		physics::collision::Material material;
	};
}
