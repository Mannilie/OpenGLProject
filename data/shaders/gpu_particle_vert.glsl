//VERTEX SHADER
#version 410

layout(location = 0) in vec3  position;
layout(location = 1) in vec3  velocity;
layout(location = 2) in float lifetime;
layout(location = 3) in float lifespan;

out vec3  geomPosition;
out float geomLifetime;
out float geomLifespan;

void main()
{
	geomPosition = position;
	geomLifetime = lifetime;
	geomLifespan = lifespan;
}

