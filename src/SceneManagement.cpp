#include "SceneManagement.h"
#include "GLM_Header.h"
#include "GL_Header.h"

#include "Gizmos.h"

#include "Vertex.h"
#include "Utility.h"

SceneManagement::SceneManagement(){}

bool SceneManagement::startup()
{
	if (Application::startup() == false)
	{
		return false;
	}

	Gizmos::create();

	//CREATE GUI FOR CAMERA INSIDE (DEBUGGING)
	GUI::createNewBar("SceneManagement");
	
	m_flyCamera = FlyCamera(60.0f, m_windowWidth / m_windowHeight, 10.0f);
	m_flyCamera.m_fieldOfView = 60.0f;
	m_flyCamera.m_aspect = m_windowWidth / m_windowHeight;
	m_flyCamera.setMoveSpeed(100.0f);
	m_flyCamera.setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	m_flyCamera.setFOVSpeed(100.0f);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	
	m_sphere;
	m_sphere.centre = vec3(0, cosf((float)glfwGetTime()) + 1, 0);
	m_sphere.radius = 0.5f;

	m_plane = vec4(0, 1, 0, -1);

	return true;
}

bool SceneManagement::update()
{
	if (Application::update() == false)
	{
		return false;
	}
	Gizmos::clear();

	Gizmos::addTransform(mat4(1));

	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	vec4 red(1, 0, 0, 1);
	vec4 green(0, 1, 0, 1);
	vec4 blue(0, 0, 1, 1);

	for (int i = 0; i <= 20; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, -10), vec3(-10 + i, 0, 10),
			i == 10 ? blue : black);
		Gizmos::addLine(vec3(-10, 0, -10 + i), vec3(10, 0, -10 + i),
			i == 10 ? red : black);
	}

	m_flyCamera.m_windowWidth = m_windowWidth;
	m_flyCamera.m_windowHeight = m_windowHeight;
	m_flyCamera.update(m_deltaTime);

	//COLLISION DETECTION

	m_sphere.draw();

	vec4 planeColor;
	
	switch (m_sphere.checkCollision(m_plane))
	{
	case 1:
		planeColor = vec4(0, 1, 0, 1); //Green
		break;
	case -1:
		planeColor = vec4(1, 1, 0, 1); //Yellow
		break;
	case 0:
		planeColor = vec4(1, 0, 0, 1); //Red
		break;
	}

	Gizmos::addTri(vec3(4, 1, 4), vec3(-4, 1, -4), vec3(-4, 1, 4),
		planeColor);
	Gizmos::addTri(vec3(4, 1, 4), vec3(4, 1, -4), vec3(-4, 1, -4),
		planeColor);

	m_sphere.centre = vec3(0, sinf(m_gameTime) + 1, 0);

	vec4 planes[6];
	getFrustumPlanes(m_flyCamera.getProjView(), planes);

	drawFrustum(m_flyCamera.m_proj);

	//for (int planeIndex = 0; planeIndex < 6; ++planeIndex)
	//{
	//}
	return true;
}

void SceneManagement::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	
	Gizmos::draw(m_flyCamera.m_projView);
	Application::draw();
}

void SceneManagement::shutdown()
{
	Application::shutdown();
}