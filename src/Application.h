#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#define GLM_SWIZZLE
#include "glm/glm.hpp"
#include "glm/ext.hpp"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class GLFWwindow;

class Application
{
protected:
	GLFWwindow* m_window;
	char* m_appName;
	int m_windowWidth;
	int m_windowHeight;
public:
	Application();
	virtual ~Application();

	void SetDefault(float a_windowWidth, float a_windowHeight, char* a_appName);
	virtual bool Startup();
	virtual bool Update();
	virtual void Draw();
	virtual void Shutdown();
};

#endif //_APPLICATION_H_