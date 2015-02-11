#include "RenderingGeometry.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>

Application* g_theApplication;

bool runApp();
void onWindowResize(GLFWwindow* window, int width, int height);

int main()
{
	RenderingGeometry theApp;
	g_theApplication = &theApp;

	theApp.SetDefault(1280, 720, "Manny's Project");

	if (theApp.Startup() == false) //Checks for error messages (< 0)
	{
		return -1;
	}

	glfwSetWindowSizeCallback(theApp.m_window, onWindowResize);
	
	while (theApp.Update() == true)
	{
		theApp.Draw();
	}

	theApp.Shutdown();
	
	return 0;
}

bool runApp()
{
	if (g_theApplication->Update() == false)
		return false;
	
	g_theApplication->Draw();

	return true;
}

void onWindowResize(GLFWwindow* window, int width, int height)
{
	runApp();
}

