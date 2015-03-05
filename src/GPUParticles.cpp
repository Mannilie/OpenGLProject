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
	m_flyCamera = FlyCamera();
	m_flyCamera.m_fieldOfView = 60.0f;
	m_flyCamera.setMoveSpeed(100.0f);
	m_flyCamera.setFOVSpeed(100.0f);
	m_flyCamera.setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	m_emitter.initialise(100000,
		vec4(0, 0, 0, 0), //Position
		0,			   //Emit rate
		0.1f,			   //Min life span
		5.0f,			   //Max life span 
		2,          //Min velocity
		10,		   //Max velocity
		1.0f,			   //Start size
		0.1f,			   //End size
		vec4(1, 0, 0, 1), //Start color
		vec4(1, 1, 0, 1));  //End color

	m_time = 0.0f;
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
	return true;
}

void GPUParticles::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::draw(m_flyCamera.m_projView);

	m_emitter.draw(m_gameTime, m_flyCamera.m_world, m_flyCamera.getProjView());

	Application::draw();
}

void GPUParticles::shutdown()
{
	Application::shutdown();
}