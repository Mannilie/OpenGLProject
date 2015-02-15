#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "GLM_Header.h"

class GUI;

struct GLFWwindow;

class Application
{
protected:
	char* m_appName;
	float m_windowWidth;
	float m_windowHeight;
	float deltaTime;
public:
	GUI* m_gui;
	GLFWwindow* m_window;

	Application();
	virtual ~Application();

	void setDefault(float a_windowWidth, float a_windowHeight, char* a_appName);
	virtual bool startup();
	virtual void shutdown();
	virtual bool update();
	virtual void draw();
};

#endif //_APPLICATION_H_