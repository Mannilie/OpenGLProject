#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "GLM_Header.h"

struct GLFWwindow;

class Application
{
protected:
	char* m_appName;
	float m_windowWidth;
	float m_windowHeight;
public:
	GLFWwindow* m_window;

	Application();
	virtual ~Application();

	void SetDefault(float a_windowWidth, float a_windowHeight, char* a_appName);
	virtual bool Startup();
	virtual void Shutdown();
	virtual bool Update();
	virtual void Draw();
};

#endif //_APPLICATION_H_