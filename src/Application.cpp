#include "Application.h"

#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>

#include <cstdio>

void window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("Window is resizing! %d.%d\n");
}

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

	glfwSetWindowSizeCallback(this->m_window, window_size_callback);

	return true;
}

bool Application::Update()
{
	if(glfwWindowShouldClose(m_window))
	{
		return false;
	}

	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	glfwGetFramebufferSize(m_window, &width, &height);
	glViewport(0, 0, m_windowWidth, m_windowHeight);

	m_windowWidth = (float)width;
	m_windowHeight = (float)height;

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
