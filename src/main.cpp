#include "Quaternions.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>

Application* g_theApplication;

bool runApp();
void onWindowResize(GLFWwindow* window, int width, int height);

int main()
{
	Quaternions theApp;
	g_theApplication = &theApp;
	theApp.setDefault(1280, 720, "Manny's Project", true);
	if (theApp.startup() == false) //Checks for error messages (< 0)
	{
		return -1;
	}
	glfwSetWindowSizeCallback(theApp.m_window, onWindowResize);
	while (theApp.update() == true)
	{
		theApp.draw();
	}
	theApp.shutdown();
	return 0;
}

bool runApp()
{
	if (g_theApplication->update() == false)
	{
		return false;
	}
	g_theApplication->draw();
	return true;
}

void onWindowResize(GLFWwindow* window, int width, int height)
{
	runApp();
}

