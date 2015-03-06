#ifndef _COLLISIONS_H_
#define _COLLISIONS_H_

#include "GLM_Header.h"
#include <vector>
using std::vector;

class AABB
{
public:
	AABB();
	~AABB();

	void reset();
	void fit(const vector<vec3>& a_points);
	
	vec3 min;
	vec3 max;
};

class BoundingSphere 
{
public:
	BoundingSphere();
	~BoundingSphere();

	void fit(const vector<vec3>& a_points);

	int checkCollision(vec4 a_plane);

	void draw();

	vec3	centre;
	float	radius;
};

void getFrustumPlanes(const mat4& a_transform, vec4* a_planes);

void drawFrustum(const mat4& a_transform);

#endif