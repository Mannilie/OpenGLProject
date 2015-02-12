#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "GLM_Header.h"

struct Vertex
{
	vec4 position;
	vec4 color;
};

struct VertexTexCoord
{
	vec4 position;
	vec2 texCoord;
};

#endif