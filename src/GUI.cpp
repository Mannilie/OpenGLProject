#include "GUI.h"
#include "GL_Header.h"

GUI* GUI::m_instance = nullptr;

GUI::GUI()
{
	TwInit(TW_OPENGL, NULL);

	m_window = glfwGetCurrentContext();
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	TwWindowSize(windowWidth, windowHeight);

	//Use these...
	myBar = TwNewBar("My new Bar");
	TwAddVarRW(myBar, "NameOfMyVariable", TW_TYPE_FLOAT, &myBarFloat, "");

	//Send window size events to AntTweakBar
	glfwSetCursorPosCallback(m_window, onCursorPos);
	glfwSetMouseButtonCallback(m_window, onMouseButton);
	glfwSetKeyCallback(m_window, onKey);
	glfwSetWindowSizeCallback(m_window, onWindowResize);
	glfwSetScrollCallback(m_window, onScroll);
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
	TwTerminate();
	delete m_instance;
	m_instance = nullptr;
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
	if (!TwEventCharGLFW(a_key, a_action))  // send event to AntTweakBar
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
void GUI::onScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	if (!TwEventMouseWheelGLFW((int)yoffset))  // send event to AntTweakBar
	{
		// event has not been handled by AntTweakBar
		// your code here to handle the event
		// ...
	}
}