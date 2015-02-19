#include "GUI.h"
#include "GL_Header.h"

GUI* GUI::m_instance = nullptr;

GUI::GUI()
{
	TwInit(TW_OPENGL_CORE, nullptr);

	m_window = glfwGetCurrentContext();
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	TwWindowSize(windowWidth, windowHeight);

	//Send window size events to AntTweakBar
	glfwSetCursorPosCallback(m_window, onCursorPos);
	glfwSetMouseButtonCallback(m_window, onMouseButton);
	glfwSetKeyCallback(m_window, onKey);
	glfwSetWindowSizeCallback(m_window, onWindowResize);
	glfwSetScrollCallback(m_window, onScroll);
	glfwSetCharCallback(m_window, onChar);
}

void GUI::create()
{
	if (m_instance == nullptr)
		m_instance = new GUI();
}

void GUI::update(float a_deltaTime)
{
	if (m_instance == nullptr)
	{
		return;
	}

	m_instance->m_window = glfwGetCurrentContext();
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_instance->m_window, &windowWidth, &windowHeight);

	TwWindowSize(windowWidth, windowHeight);
}

void GUI::draw()
{
	if (m_instance == nullptr)
	{
		return;
	}
	TwDraw();
}

void GUI::destroy()
{
	TwDeleteAllBars();
	TwTerminate();
	delete m_instance;
	m_instance = nullptr;
}

void GUI::createNewBar(char* a_barTitle)
{
	m_instance->m_tweakBars[a_barTitle] = TwNewBar(a_barTitle);
}

TwBar* GUI::getBar(char* a_barTitle)
{
	if (m_instance->m_tweakBars.find(a_barTitle) != m_instance->m_tweakBars.end())
	{
		return m_instance->m_tweakBars[a_barTitle];
	}
	return NULL;
}

//AntTweakBar GLFW event callbacks

void GUI::onCursorPos(GLFWwindow* a_window, double a_mouseX, double a_mouseY)
{
	if (!TwEventMousePosGLFW((int)a_mouseX, (int)a_mouseY))  // send event to AntTweakBar
	{	
		// event has not been handled by AntTweakBar
		// your code here to handle the event
		// ...
	}
}
void GUI::onMouseButton(GLFWwindow* a_window, int a_button, int a_action, int a_mods)  // your callback function called by GLFW when mouse has moved
{
	if (!TwEventMouseButtonGLFW(a_button, a_action))  // send event to AntTweakBar
	{
		// event has not been handled by AntTweakBar
		// your code here to handle the event
		// ...
	}
}
void GUI::onKey(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods)
{
	if (!TwEventKeyGLFW(a_key, a_action))  // send event to AntTweakBar
	{
		// event has not been handled by AntTweakBar
		// your code here to handle the event
		// ...
	}
}
void GUI::onWindowResize(GLFWwindow* a_window, int a_width, int a_height)
{
	if (!TwWindowSize(a_width, a_height))  // send event to AntTweakBar
	{ 
		// event has not been handled by AntTweakBar
		// your code here to handle the event
		// ...
	}
}
void GUI::onScroll(GLFWwindow* a_window, double a_xScroll, double a_yScroll)
{
	if (!TwEventMouseWheelGLFW((int)a_yScroll))  // send event to AntTweakBar
	{
		// event has not been handled by AntTweakBar
		// your code here to handle the event
		// ...
	}
}


void GUI::onChar(GLFWwindow* a_window, unsigned int c)
{
	if (!TwEventCharGLFW(c, GLFW_PRESS))
	{
		// event has not been handled by AntTweakBar
		// your code here to handle the event
		// ...
	}
}