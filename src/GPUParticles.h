#ifndef _GPUPARTICLES_H_
#define _GPUPARTICLES_H_

#include "Application.h"
#include "Camera.h"

#include "GPUEmitter.h"

class GPUParticles : public Application
{
public:
	GPUParticles();
	virtual bool startup();
	virtual bool update();
	virtual void draw();
	virtual void shutdown();

	FlyCamera m_flyCamera;
	unsigned int m_program;

	GPUPointEmitter m_emitter;

	float m_time;
};

#endif
