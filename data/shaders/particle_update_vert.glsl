#version 410

in vec3  position;
in vec3  velocity;
in float lifetime;
in float lifespan;

out vec3  updatedPosition;
out vec3  updatedVelocity;
out float updatedLifetime;
out float updatedLifespan;

uniform float deltaTime;
uniform vec3  emitterPosition;

uniform float minVelocity;
uniform float maxVelocity;

uniform float minLifespan;
uniform float maxLifespan;

uniform float time;

const float INVERSE_MAX_UINT = 1.0f / 4294967295.0f;

float rand(uint seed, float range) 
{
	uint i = (seed ^ 12345391u) * 2654435769u;
	i ^= (i << 6u) ^ (i >> 26u);
	i *= 2654435769u;
	i += (i << 5u) ^ (i >> 12u);
	return float(range * i) * INVERSE_MAX_UINT;
}

void main()
{
	//move particles based on velocity 
	updatedPosition = position + velocity * deltaTime;
	updatedVelocity = velocity;
	updatedLifespan = lifespan;

	//update the lifetime based on delta time
	updatedLifetime = lifetime + deltaTime;

	//spawn new particles if we need to	
	if( updatedLifetime > lifespan)
	{
		updatedPosition = emitterPosition;
		
		//set its velocity
		float velRang = maxVelocity - minVelocity;
		
		uint seed = uint(gl_VertexID + (time * 1000));
		float velLen = rand(seed++, velRang) + minVelocity;
		
		updatedVelocity.x = rand(seed++, 2) - 1;
		updatedVelocity.y = rand(seed++, 2) - 1;
		updatedVelocity.z = rand(seed++, 2) - 1;
		updatedVelocity = normalize(updatedVelocity) * velRang;

		//set its lifespan
		updatedLifetime = 0;
		float lifespanRange = maxLifespan - minLifespan;
		updatedLifespan = rand(seed++, lifespanRange) + minLifespan;
	}
}