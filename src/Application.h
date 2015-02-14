#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "GLM_Header.h"

struct GLFWwindow;

class Application
{
protected:
	char* m_appName;
public:
	GLFWwindow* m_window;
	float m_windowWidth;
	float m_windowHeight;

	Application();
	virtual ~Application();

	void setDefault(float a_windowWidth, float a_windowHeight, char* a_appName);
	virtual bool startup();
	virtual void shutdown();
	virtual bool update();
	virtual void draw();
};

#endif //_APPLICATION_H_