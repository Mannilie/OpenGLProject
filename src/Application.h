#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>

#define GLM_SWIZZLE
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Application
{
protected:
	GLFWwindow* m_Window;
public:
	Application();
	~Application();
	virtual int Startup() = 0;
	virtual void Shutdown() = 0;
	virtual int Update() = 0;
	virtual void Draw() = 0;
};



#endif