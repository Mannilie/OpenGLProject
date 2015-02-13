#include "Texturing.h"
#include "GLM_Header.h"

#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "Gizmos.h"

#include "Vertex.h"
#include "Utility.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool Texturing::Startup()
{
	if (Application::Startup() == false)
	{
		return false;
	}

	Gizmos::create();

	loadTexture("./textures/crate.png");
	loadShaders("./shaders/textured_vertex.glsl", "./shaders/textured_fragment.glsl", &m_program);
	GenerateQuat(5.0f);

	m_Camera = FlyCamera(60.0f, m_windowWidth / m_windowHeight, 10.0f);
	m_Camera.m_fieldOfView = 60.0f;
	m_Camera.m_aspect = m_windowWidth / m_windowHeight;
	m_Camera.setMoveSpeed(100.0f);
	m_Camera.setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	m_Camera.setFOVSpeed(100.0f);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	return true;
}

void Texturing::Shutdown()
{


	Application::Shutdown();
}

bool Texturing::Update()
{
	if (Application::Update() == false)
	{
		return false;
	}

	float deltaTime = (float)glfwGetTime();
	glfwSetTime(0.0f);

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

	m_Camera.m_windowWidth = m_windowWidth;
	m_Camera.m_windowHeight = m_windowHeight;
	m_Camera.update(deltaTime);

	return true;
}

void Texturing::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(m_program);
	unsigned int projViewHandle = glGetUniformLocation(m_program, "projView");
	if (projViewHandle >= 0)
	{
		glUniformMatrix4fv(projViewHandle, 1, GL_FALSE, (float*)&m_Camera.m_projView);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		int diffuseLocation = glGetUniformLocation(m_program, "diffuse");

		glUniform1i(diffuseLocation, 0);
	}

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	Gizmos::draw(m_Camera.m_projView);

	Application::Draw();
}

void Texturing::loadTexture(const char* a_filename)
{
	int width;
	int height;
	int channels;

	unsigned char *data = stbi_load(a_filename, &width, &height, &channels, STBI_default);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	stbi_image_free(data);
}

void Texturing::GenerateQuat(float a_size)
{
	VertexTexCoord vertexData[4];

	vertexData[0].position = vec4(-a_size, 0, -a_size, 1);
	vertexData[1].position = vec4(-a_size, 0, a_size, 1);
	vertexData[2].position = vec4(a_size, 0, a_size, 1);
	vertexData[3].position = vec4(a_size, 0, -a_size, 1);

	vertexData[0].texCoord = vec2(0, 0);
	vertexData[1].texCoord = vec2(0, 1);
	vertexData[2].texCoord = vec2(1, 1);
	vertexData[3].texCoord = vec2(1, 0);
	
	unsigned int indexData[6] = { 0, 2, 1,
								  0, 3, 2 };
	
	glGenVertexArrays(1, &m_VAO);
	
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexTexCoord)*4, vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*6, indexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //position
	glEnableVertexAttribArray(1); //tex coord

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexTexCoord), 0);	//position
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTexCoord), (void*)sizeof(vec4)); //tex coord

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}