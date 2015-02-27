#include "GPUParticles.h"
#include "GLM_Header.h"
#include "GL_Header.h"

#include "Gizmos.h"

#include "Vertex.h"
#include "Utility.h"

GPUParticles::GPUParticles()
{

}

bool GPUParticles::startup()
{
	if (Application::startup() == false)
	{
		return false;
	}

	Gizmos::create();

	//CREATE GUI FOR CAMERA INSIDE (DEBUGGING)
	m_flyCamera = FlyCamera(60.0f, m_windowWidth / m_windowHeight, 10.0f);
	m_flyCamera.m_fieldOfView = 60.0f;
	m_flyCamera.m_aspect = m_windowWidth / m_windowHeight;
	m_flyCamera.setMoveSpeed(100.0f);
	m_flyCamera.setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	m_flyCamera.setFOVSpeed(100.0f);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	m_emitter.init(10000,
		vec3(0, 0, 0), //Position
		0,			   //Emit rate
		3,			   //Min life span
		3,			   //Max life span 
		0.8f,          //Min velocity
		1.0f,		   //Max velocity
		0.1f,			   //Start size
		0.01f,			   //End size
		vec4(1, 0.4, 0, 1), //Start color
		vec4(1, 0, 0, 1));  //End color

	m_time = 0;
	return true;
}

bool GPUParticles::update()
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

	m_time += m_deltaTime;
	return true;
}

void GPUParticles::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_emitter.draw(m_time, m_flyCamera.m_world, m_flyCamera.m_projView);

	Gizmos::draw(m_flyCamera.m_projView);

	Application::draw();
}

void GPUParticles::shutdown()
{
	Application::shutdown();
}