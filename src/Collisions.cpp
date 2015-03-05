#include "Collisions.h"

#include <iostream>

using std::cout;
using std::endl;

#include "Gizmos.h"

//AABB

AABB::AABB()
{
	reset();
}

AABB::~AABB(){}

void AABB::reset()
{
	min = vec3(1e37f);
	max = vec3(-1e37f);
}

void AABB::fit(const vector<vec3>& a_points)
{
	for (auto& p : a_points)
	{
		if (p.x < min.x) min.x = p.x;
		if (p.y < min.y) min.y = p.y;
		if (p.z < min.z) min.z = p.z;
		if (p.x > min.x) min.x = p.x;
		if (p.y > min.y) min.y = p.y;
		if (p.z > min.z) min.z = p.z;
	}
}

//BoundingSphere

BoundingSphere::BoundingSphere() : 
	centre(0),
	radius(0)
{}

BoundingSphere::~BoundingSphere(){}

void BoundingSphere::fit(const vector<vec3>& a_points)
{
	vec3 min(1e37f), max(-1e37f);

	for (auto& p : a_points)
	{
		if (p.x < min.x) min.x = p.x;
		if (p.y < min.y) min.y = p.y;
		if (p.z < min.z) min.z = p.z;
		if (p.x > min.x) min.x = p.x;
		if (p.y > min.y) min.y = p.y;
		if (p.z > min.z) min.z = p.z;
	}

	centre = (min + max) * 0.5f;
	radius = glm::distance(min, centre);
}

int BoundingSphere::checkCollision(vec4 a_plane)
{
	float dotResult = glm::dot(vec3(a_plane), this->centre) + a_plane.w;

	if (dotResult > this->radius)
	{
		cout << "Front" << endl; 
		return 1;
	}
	else if (dotResult < -this->radius)
	{
		cout << "Back" << endl;
		return -1;
	}
	else
	{
		cout << "On the plane" << endl;
		return 0;
	}
}

//GIZMOS

void BoundingSphere::draw()
{
	Gizmos::addSphere(this->centre, this->radius,
		8, 8, vec4(1, 0, 1, 1));
}

//FRUSTUM

void getFrustumPlanes(const mat4& a_transform, vec4* a_planes)
{
	//Right side
	a_planes[0] = vec4(a_transform[0][3] - a_transform[1][0],
					 a_transform[1][3] - a_transform[1][0],
					 a_transform[2][3] - a_transform[2][0],
					 a_transform[3][3] - a_transform[3][0]);

	//Left side
	a_planes[1] = vec4(a_transform[0][3] + a_transform[0][0],
					 a_transform[1][3] + a_transform[1][0],
					 a_transform[2][3] + a_transform[2][0],
					 a_transform[3][3] + a_transform[3][0]);
	//Top
	a_planes[2] = vec4(a_transform[0][3] - a_transform[0][1],
					 a_transform[1][3] - a_transform[1][1],
					 a_transform[2][3] - a_transform[2][1],
					 a_transform[3][3] - a_transform[3][1]);
	//Bottom
	a_planes[3] = vec4(a_transform[0][3] + a_transform[0][1],
					 a_transform[1][3] + a_transform[1][1],
					 a_transform[2][3] + a_transform[2][1],
					 a_transform[3][3] + a_transform[3][1]);
	//Far
	a_planes[4] = vec4(a_transform[0][3] - a_transform[0][2],
					 a_transform[1][3] - a_transform[1][2],
					 a_transform[2][3] - a_transform[2][2],
					 a_transform[3][3] - a_transform[3][2]);
	
	//Near
	a_planes[5] = vec4(a_transform[0][3] + a_transform[0][2],
					 a_transform[1][3] + a_transform[1][2],
					 a_transform[2][3] + a_transform[2][2],
					 a_transform[3][3] + a_transform[3][2]);

	for (int planeIndex = 0; planeIndex < 6; planeIndex++)
	{
		a_planes[planeIndex] = glm::normalize(a_planes[planeIndex]);
	}

}


void drawFrustum(const mat4& a_transform)
{

}