#pragma once
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "InputState.h"
#include "Body.h"
#include "UnitForces.h"

namespace sge {

	namespace  physics
	{
		struct Particle
		{
			glm::mat4 placement{};
			glm::vec3 velocity{};
			glm::vec3 accelleration{};
			glm::vec3 rotation{};
			glm::vec3 d_rotation{};
			float linear_inertia{ 0.5f };
			float rotational_inertia{ 0.1f };
			float top_linear_speed{ 1 };
			float top_angular_speed{ 1 };
		};

		static auto constexpr top_speed{ 10.f };

		void inline handle_player_input(Particle &p)
		{
			auto linear_speed{ glm::length(p.velocity) };

			if (linear_speed < p.top_linear_speed)
			{
				if (input_state::w_pressed())
					p.accelleration += (p.placement*glm::vec4{ 0,(1 / p.linear_inertia), 0, 0 })[3];
				if (input_state::s_pressed())
					p.accelleration += (p.placement*glm::vec4{ 0, -(1 / p.linear_inertia), 0, 0 })[3];
			}

			//TODO problem with what follows: if you rotate rotate left very fast you can't slow down by holding right
			auto rotational_speed{ glm::length(p.rotation) };

			if (rotational_speed < p.top_angular_speed)
			{
				if (input_state::a_pressed())
					p.d_rotation += (1 / p.rotational_inertia) * force::unit::anti_clockwise;
				if (input_state::d_pressed())
					p.d_rotation += (1 / p.rotational_inertia) * force::unit::clockwise;
			}
		}

		void inline step(Particle &p, const float &dt)
		{
			// Symplectic Euler integration: velocities first, then positions 
			p.velocity += p.accelleration*dt;
			p.rotation += p.d_rotation*dt;

			auto rot = p.rotation;
			p.placement = glm::translate(p.placement,p.velocity)*glm::rotate(glm::length(rot), rot)*std::powf(dt, 2);;
			//glm::rotate(glm::translate(p.placement, p.velocity.linear*dt),);
			//p.placement.orientation += p.velocity.angular*dt;

			// "friction"
			p.velocity *= .95f;
			p.rotation *= .95f;
		}

		namespace collision
		{
			struct AABB
			{
				glm::vec2 top_left{ 0,1 };
				glm::vec2 bottom_right{ 1,0 };
			};


			struct BoundingCircle
			{
				glm::vec2 position;
				float radius;
			};

			//COMMON VALUES (from tutorial):
			//Rock       Density : 0.6  Restitution : 0.1
			//Wood       Density : 0.3  Restitution : 0.2
			//Metal      Density : 1.2  Restitution : 0.05
			//BouncyBall Density : 0.3  Restitution : 0.8
			//SuperBall  Density : 0.3  Restitution : 0.95
			//Pillow     Density : 0.1  Restitution : 0.2
			//Static     Density : 0.0  Restitution : 0.4

			struct Material
			{
				float density{ 0.3f };
				float restitution{ 0.2f };
			};

			struct Collision
			{
				//Body* A;
				//Body* B;
				float penetration;
				glm::vec2 normal;
			};

			namespace coarse
			{
				inline bool CirclevsCircle(BoundingCircle a, BoundingCircle b)
				{
					auto r = std::pow(a.radius + b.radius, 2);
					auto sum = a.position + b.position;
					return r < glm::dot(sum, sum);
				}

				inline bool AABBvsAABB(AABB a, AABB b)
				{
					if (a.top_left.x < b.bottom_right.x || a.bottom_right.x > b.top_left.x) return false;
					if (a.top_left.y < b.bottom_right.y || a.bottom_right.y > b.top_left.y) return false;
					return true;
				}
			}

			void inline ResolveCollision(Collision c)
			{
				//sge::Body *A = c.A;
				//sge::Body *B = c.B;


				//glm::vec2 rel_vel = B->velocity - A->velocity;
				//float velAlongNormal = glm::dot(rel_vel, c.normal);
				//
				//if (velAlongNormal > 0)
				//	return;
				//
				//float e = std::fminf(A->material.restitution, B->material.restitution);
				//
				//float j = -(1 + e) * velAlongNormal;
				//j /= A->mass_data.mass_inv + B->mass_data.mass_inv;
				//
				//glm::vec2 impulse = j*c.normal;
				//A->velocity -= A->mass_data.mass_inv * impulse;
				//B->velocity += B->mass_data.mass_inv * impulse;
			}

			//void PositionalCorrection(Obj A, Obj B)
			//{
			//	const float percent{ 0.2 };	//0.2-0.8
			//	const float slop{ 0.1 };		//0.01-0.1
			//	glm::vec2 correction = std::max(penetration - k_slop, 0.0f) / (A.inv_mass + B.inv_mass) * percent * normal;
			//	A.position -= A.inv_mass * correction;
			//	B.position += B.inv_mass * correction;
			//}
		}
	};
}

// To be developed and integrate.
/*
// Collision etc
//http://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331

bool AABBvsAABB(Manifold *m)
{
Particle *A = m->A;
Particle *B = m->B;

glm::vec2 n = B->pos - A->pos;

AABB abox = A->aabb;
AABB bbox = B->aabb;

// Calculate half extents along x axis for each object
float a_extent = (abox.max.x - abox.min.x) / 2;
float b_extent = (bbox.max.x - bbox.min.x) / 2;

// Calculate overlap on x axis
float x_overlap = a_extent + b_extent - std:abs(n.x);

// SAT test on x axis
if (x_overlap > 0)
{
float a_extent = (abox.max.y - abox.min.y) / 2;
float b_extent = (bbox.max.y - bbox.min.y) / 2;

float y_overlap = a_extent + b_extent - std::abs(n.y);

if (y_overlap > 0)
{
// Find out which axis is axis of least penetration
if (x_overlap > y_overlap)
{
// Point towards B knowing that n points from A to B
if (n.x < 0)
m->normal = glm::vec2(-1, 0);
else
m->normal = glm::vec2(0, 0);
m->penetration = x_overlap;
return true;
}
else
{
// Point toward B knowing that n points from A to B
if (n.y < 0)
m->normal = glm::vec2(0, -1);
else
m->normal = glm::vec2(0, 1);

m->penetration = y_overlap;
return true;
}
}
}

//TODO: CLEAN UP
bool AABBvsCircle(Manifold *m)
{
Object *A = m->A
Object *B = m->B

glm::vec2 n = B->pos - A->pos;

glm::vec2 closest = n; // = closestPointOnAtoCenterOfB(n);

float x_extent = (A->aabb.max.x - A->aabb.min.x) / 2;
float y_extent = (A->aabb.max.y - A->aabb.min.y) / 2;

closest.x = clamp(closest.x, -x_extent, x_extent); // Order: closest ... or ... closest
closest.y = clamp(closest.y, -y_extent, y_extent);

bool inside = false;

// Circle is inside the AABB, so we need to clamp the circle's center
// to the closest edge
if (n == closest)
{
inside = true;

// Find closest axis
if (abs(n.x) > abs(n.y))
{
// Clamp to closest extent
if (closest.x > 0)
closest.x = x_extent;
else
closest.x = -x_extent;
}
else // y axis is shorter
{
// Clamp to closest extent
if (closest.y > 0)
closest.y = y_extent;
else
closest.y = -y_extent;
}
}

glm::vec2 normal = n - closest;
float d = glm::dot(normal, normal);
float r = B->radius;

if (d > r * r && !inside)
return false;

d = std::sqrt(d);

if (inside)
{
m->normal = -n
m->penetration = r - d;
}
else
{
m->normal = n;
m->penetration = r - d;
}

return true;
}

bool CirclevsCircle(Manifold *m)
{
Object *A = m->A;
Object *B = m->B;

glm::vec2 n = B->pos - A->pos; // Vector from A to B.

float r = A->radius + B->radius;

if (glm::dot(n, n) > std::pow(r, 2))
return false;

float dist = glm::length(n);

if (dist != 0)
{
m->penetration = r - dist; // difference between radius and distance ... must
m->normal = n / d;
}

else
{	// Arbitrary but consistent values
m->penetration = A->radius;
m->normal = glm::vec2(1, 0);
return true;
}
}

// Normal of ax + by + c = 0 is (a, b) (normalized)



BROAD PHASE ALGORITHM :
struct Pair
{
body *A;
body *B;
};

void BroadPhase::GeneratePairs(void)
{
pairs.clear()

// Cache space for AABBs to be used in computation
// of each shape's bounding box
AABB A_aabb
AABB B_aabb

for (i = bodies.begin(); i != bodies.end(); i = i->next)
{
for (j = bodies.begin(); j != bodies.end(); j = j->next)
{
Body *A = &i->GetData()
Body *B = &j->GetData()

// Skip check with self
if (A == B)
continue

A->ComputeAABB(&A_aabb)
B->ComputeAABB(&B_aabb)

if (AABBtoAABB(A_aabb, B_aabb))
pairs.push_back(A, B)
}
}
}

// Sort pairs to expose duplicates
sort(pairs, pairs.end(), SortPairs);

// Queue manifolds for solving
{
int i = 0;
while (i < pairs.size())
{
Pair *pair = pairs.begin() + i;
uniquePairs.push_front(pair);

++i;

// Skip duplicate pairs by iterating i until we find a unique pair
while (i < pairs.size())
{
Pair *potential_dup = pairs + i;
if (pair->A != potential_dup->B || pair->B != potential_dup->A)
break;
++i;
}
}
}


bool SortPairs(Pair lhs, Pair rhs)
{
if (lhs.A < rhs.A)
return true;

if (lhs.A == rhs.A)
return lhs.B < rhs.B;

return false;
}


LAYERING:
// Generates the pair list.
// All previous pairs are cleared when this function is called.
void BroadPhase::GeneratePairs(void)
{
pairs.clear()

// Cache space for AABBs to be used in computation
// of each shape's bounding box
AABB A_aabb
AABB B_aabb

for (i = bodies.begin(); i != bodies.end(); i = i->next)
{
for (j = bodies.begin(); j != bodies.end(); j = j->next)
{
Body *A = &i->GetData()
Body *B = &j->GetData()

// Skip check with self
if (A == B)
continue

// Only matching layers will be considered
if (!(A->layers & B->layers))
continue;

A->ComputeAABB(&A_aabb)
B->ComputeAABB(&B_aabb)

if (AABBtoAABB(A_aabb, B_aabb))
pairs.push_back(A, B)
}
}
}

//half space detection: check sign of ax+by+c
*/