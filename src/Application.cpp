#include "Application.h"
#include "GL_Header.h"
#include <cstdio>

Application::Application() 
	: m_windowWidth(0)
	, m_windowHeight(0)
	, m_appName("")
{}

Application::~Application(){}

void Application::setDefault(float a_windowWidth, float a_windowHeight, char* a_appName, bool a_debugging)
{ 
	m_windowWidth = a_windowWidth;
	m_windowHeight = a_windowHeight;
	m_appName = a_appName;
	m_debugging = a_debugging;
}

bool Application::startup()
{
	if (m_windowWidth == 0 || m_windowHeight == 0 || m_appName == "")
	{
		m_windowWidth = 1280.0f;
		m_windowHeight = 700.0f;
		m_appName = "Default Project";
	}
	
	if (glfwInit() == false)
	{
		return false;
	}

	this->m_window = glfwCreateWindow((int)m_windowWidth, (int)m_windowHeight, m_appName, nullptr, nullptr);

	if (this->m_window == nullptr)
	{
		return false;
	}

	glfwMakeContextCurrent(this->m_window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(this->m_window);
		glfwTerminate();
		return false;
	}

	int major_version = ogl_GetMajorVersion();
	int minor_version = ogl_GetMinorVersion();

	printf("successfully loaded OpenGL version %d.%d\n", major_version, minor_version);

	if (m_debugging) //Enable debugging
	{
		GUI::create();
	}

	return true;
}

void Application::shutdown()
{
	GUI::destroy();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Application::update()
{
	if(glfwWindowShouldClose(m_window))
	{
		return false;
	}
	m_deltaTime = (float)glfwGetTime();
	glfwSetTime(0.0f);

	GUI::update(m_deltaTime);

	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	glfwGetFramebufferSize(m_window, &width, &height);
	glViewport(0, 0, (int)m_windowWidth, (int)m_windowHeight);

	m_windowWidth = (float)width;
	m_windowHeight = (float)height;
	return true;
}

void Application::draw()
{
	GUI::draw();

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}