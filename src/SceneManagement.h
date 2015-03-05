#ifndef _SCENEMANAGEMENT_H_
#define _SCENEMANAGEMENT_H_

#include "Application.h"
#include "Camera.h"

#include "Collisions.h"

class SceneManagement : public Application
{
public:
	SceneManagement();
	virtual bool startup();
	virtual bool update();
	virtual void draw();
	virtual void shutdown();

	FlyCamera		m_flyCamera;
	unsigned int	m_program;

	//COLLISION ITEMS
	BoundingSphere	m_sphere;
	vec4			m_plane;

};

#endif