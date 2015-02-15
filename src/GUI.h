#ifndef _GUI_H_
#define _GUI_H_

#include <AntTweakBar.h>
struct GLFWwindow;

class GUI
{
private:
	TwBar *myBar;
	float myBarFloat;
public:
	GLFWwindow* m_window;
	static GUI* m_instance;

	GUI();
	static void create();
	static void update(float a_deltaTime);
	static void draw();
	static void	destroy();

	//AntTweakBar GLFW event callbacks
	static void onCursorPos(GLFWwindow* a_window, double a_mouseX, double a_mouseY);
	static void onMouseButton(GLFWwindow* a_window, int a_button, int a_action, int a_mods);
	static void onKey(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
	static void onWindowResize(GLFWwindow* a_window, int a_width, int a_height);
	static void onScroll(GLFWwindow* window, double xoffset, double yoffset);
};

#endif