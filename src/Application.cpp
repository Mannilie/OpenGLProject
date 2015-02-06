#include "Application.h"

#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>

#include <cstdio>

Application::Application() 
	: m_windowWidth(0)
	, m_windowHeight(0)
	, m_appName("")
{}
Application::~Application(){}


void Application::SetDefault(float a_windowWidth, float a_windowHeight, char* a_appName)
{ 
	m_windowWidth = a_windowWidth;
	m_windowHeight = a_windowHeight;
	m_appName = a_appName;
}

bool Application::Startup()
{
	if (m_windowWidth == 0 || m_windowHeight == 0 || m_appName == "")
	{
		m_windowWidth = 1280;
		m_windowHeight = 700;
		m_appName = "Default Project";
	}
	
	if (glfwInit() == false)
	{
		return false;
	}

	this->m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_appName, nullptr, nullptr);

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
	return true;
}

bool Application::Update()
{
	if(glfwWindowShouldClose(m_window))
	{
		return false;
	}

	glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
	glfwGetFramebufferSize(m_window, &m_windowWidth, &m_windowHeight);
	glViewport(0, 0, m_windowWidth, m_windowHeight);

	return true;
}

void Application::Draw()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Application::Shutdown()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
