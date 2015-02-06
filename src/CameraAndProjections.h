#ifndef _CAM_PROJ_H_
#define _CAM_PROJ_H_

#include "Application.h"
#include "Camera.h"

class CameraAndProjections : public Application
{
private:
	FlyCamera m_Camera;
public:
	CameraAndProjections();
	virtual bool Startup();
	virtual bool Update();
	virtual void Draw();
	virtual void Shutdown();
};


#endif //_CAM_PROJ_H_