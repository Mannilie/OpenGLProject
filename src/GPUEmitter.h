#ifndef _GPUEMITTER_H_
#define _GPUEMITTER_H_

#include "GLM_Header.h"

//gpu particle struct
struct GPUParticle
{
	GPUParticle() : lifetime(1), lifespan(0){}
	vec3	position;
	vec3	velocity;
	float	lifetime;
	float	lifespan;
};

//gpu emitter class
	//creating gpu buffers
	//setting up stuff for transform feedback
	//creating the shaders
	//actually rendering them
class GPUPointEmitter
{
public:
	GPUPointEmitter(); 
	~GPUPointEmitter();
	
	void initialise(unsigned int a_maxParticles,
		vec4  a_position,
		float a_emitRate,
		float a_minLifespan,
		float a_maxLifespan,
		float a_minVelocity,
		float a_maxVelocity,
		float a_startSize,
		float a_endSize,
		vec4  a_startColor,
		vec4  a_endColor);
	
	void draw(float a_currTime,
		mat4 a_cameraTransform,
		mat4 a_projectionView);

	void createBuffers();
	void createUpdateShader();
	void createDrawShader();

	float	m_emitRate; //extra

	GPUParticle* m_particles;

	unsigned int m_maxParticles;

	vec4	m_position;

	float	m_minLifespan;
	float	m_maxLifespan;
	
	float	m_minVelocity;
	float	m_maxVelocity;
	
	float	m_startSize;
	float	m_endSize;
	
	vec4	m_startColor;
	vec4	m_endColor;

	unsigned int m_activeBuffer;
	unsigned int m_VAO[2];
	unsigned int m_VBO[2];

	unsigned int m_drawShader;
	unsigned int m_updateShader;

	float m_lastDrawTime;
};


#endif