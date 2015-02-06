#ifndef _INTROTOOPENGL_H_
#define _INTROTOOPENGL_H_

#include "Application.h"

class IntroToOpenGL : public Application
{
private:
	mat4 m_projection;
	mat4 m_view;
	float m_cameraX;
	float m_cameraZ;
	float m_timer;
public:
	virtual bool Startup();
	virtual bool Update();
	virtual void Draw();
	virtual void Shutdown();

	mat4 BuildOrbitMatrix(float local_rotation, float radius, float orbit_rotation);
};


#endif