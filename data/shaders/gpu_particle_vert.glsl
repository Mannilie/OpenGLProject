//VERTEX SHADER
#version 410

in vec3  position;
in vec3  velocity;
in float lifetime;
in float lifespan;

out vec3  geomPosition;
out float geomLifetime;
out float geomLifespan;

void main()
{
	geomPosition = position;
	geomLifespan = lifespan;
	geomLifetime = lifetime;
}

