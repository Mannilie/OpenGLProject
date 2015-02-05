#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>

#include <cstdio>

#include "Gizmos.h"

#define GLM_SWIZZLE
#include "glm/glm.hpp"
#include "glm/ext.hpp"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

mat4 BuildOrbitMatrix(float local_rotation, float radius, float orbit_rotation)
{
	mat4 result = glm::rotate(orbit_rotation, vec3(0, 1, 0)) * 
					glm::translate(vec3(radius, 0, 0)) * 
						glm::rotate(local_rotation, vec3(0, 1, 0));

	return result;
}

int main()
{
	if (glfwInit() == false)
		return -1;
	
	
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics - EV", nullptr, nullptr);

	if (window == nullptr)
		return -2;

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	int major_version = ogl_GetMajorVersion();
	int minor_version = ogl_GetMinorVersion();

	printf("successfully loaded OpenGL version %d.%d\n", major_version, minor_version);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Gizmos::create();

	mat4 projection = glm::perspective(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);

	float camera_x = -10.0f;
	float camera_z = -10.0f;

	float timer = 0.0f;
	
	glfwSetTime(0.0f);

	while (glfwWindowShouldClose(window) == false)
	{ 
		float delta = (float)glfwGetTime();
		glfwSetTime(0.0f);
		
		timer += delta;
		camera_x = sinf(timer) * 10;
		camera_z = cosf(timer) * 10;

		//mat4 view = glm::lookAt(vec3(camera_x, 10, camera_z), vec3(0, 0, 0), vec3(0, 1, 0));
		mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Gizmos::clear();

		Gizmos::addTransform(mat4(1));

		vec4 white(1);
		vec4 black(0, 0, 0, 1);
		vec4 red(1, 0, 0, 1);
		vec4 green(0, 1, 0, 1);
		vec4 blue(0, 0, 1, 1);

		for (int i = 0; i <= 20; ++i)
		{
			Gizmos::addLine(vec3(-10 + i, 0, -10), vec3(-10 + i, 0 , 10),
				i == 10 ? white : black);
			Gizmos::addLine(vec3(-10, 0, -10 + i), vec3(10, 0, -10 + i), 
				i == 10 ? white : black);
		}

		mat4 sun_transform = BuildOrbitMatrix(timer, 0, 0);

		mat4 planet_1 = sun_transform * BuildOrbitMatrix(timer * 5, 5, timer * 0.5f);
		mat4 planet_2 = sun_transform * BuildOrbitMatrix(timer * 3, 3.5f, timer * 1.5f);
		mat4 planet_3 = sun_transform * BuildOrbitMatrix(timer * 2, 6, timer * 0.25f);
		mat4 planet_4 = sun_transform * BuildOrbitMatrix(timer * 15, 2, timer * 5.0f);

		Gizmos::addSphere(sun_transform[3].xyz, 2.0f, 20, 20, red, &sun_transform);

		//Gizmos::addSphere(planet_1[3].xyz, 1.0f, 20, 20, red, &planet_1);
		//Gizmos::addSphere(planet_2[3].xyz, 0.5f, 10, 10, green, &planet_2);
		//Gizmos::addSphere(planet_3[3].xyz, 0.3f, 10, 10, blue, &planet_3);
		//Gizmos::addSphere(planet_4[3].xyz, 0.3f, 10, 10, blue, &planet_4);

		for (int planet_index = 0;
			planet_index < 15;
			++planet_index)
		{
			mat4 planet_max = sun_transform * BuildOrbitMatrix(timer / (float)planet_index, 
												(5 + planet_index) / 2.0f, 
													timer / (float)planet_index);
			Gizmos::addSphere(planet_max[3].xyz, 0.4f, 10, 10, blue, &planet_max);
		}

		//mat4 translation_matrix = glm::translate(vec3(5, 0, 0));
		//mat4 transform = rotation * translation_matrix;
		Gizmos::addAABBFilled(vec3(0, 5, 1), vec3(1, 1, 1), blue);
		//Gizmos::addAABB(vec3(0, 5, 1), vec3(1, 1, 1), blue);
	    //Gizmos::addTri(vec3(0, 1, 0), vec3(2, -1, 1), vec3(-3, -2, 4), green);

		Gizmos::draw(projection, view);

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Gizmos::destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}