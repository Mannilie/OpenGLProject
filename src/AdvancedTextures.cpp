#include "AdvancedTextures.h"
#include "GLM_Header.h"

#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "Gizmos.h"

#include "Vertex.h"
#include "Utility.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

AdvancedTextures::AdvancedTextures()
{
}

bool AdvancedTextures::Startup()
{
	if (Application::Startup() == false)
	{
		return false;
	}

	Gizmos::create();

	loadTextures();
	loadShaders("./shaders/normal_mapped_vertex.glsl", "./shaders/normal_mapped_fragment.glsl", &m_program);
	GenerateQuat(5.0f);

	m_flyCamera = FlyCamera(60.0f, m_windowWidth / m_windowHeight, 10.0f);
	m_flyCamera.m_fieldOfView = 60.0f;
	m_flyCamera.m_aspect = m_windowWidth / m_windowHeight;
	m_flyCamera.setMoveSpeed(10.0f);
	m_flyCamera.setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	m_flyCamera.setFOVSpeed(100.0f);

	m_ambientLight = vec3(0.1f);
	m_lightDir = (vec3(-1, -1, 0));
	m_lightColor = vec3(0.7f);
	m_specularPower = 15;

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	return true;
}

void AdvancedTextures::Shutdown()
{


	Application::Shutdown();
}

bool AdvancedTextures::Update()
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

	m_lightDir = (glm::rotate(deltaTime, vec3(0, 1, 0)) * vec4(m_lightDir, 0)).xyz;

	m_flyCamera.m_windowWidth = m_windowWidth;
	m_flyCamera.m_windowHeight = m_windowHeight;
	m_flyCamera.update(deltaTime);
	return true;
}

void AdvancedTextures::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);
	unsigned int projViewHandle = glGetUniformLocation(m_program, "projView");
	if (projViewHandle >= 0)
	{
		glUniformMatrix4fv(projViewHandle, 1, GL_FALSE, (float*)&m_flyCamera.m_projView);

		int ambientUniform =
			glGetUniformLocation(m_program, "ambientLight");
		int lightDirUniform =
			glGetUniformLocation(m_program, "lightDir");
		int lightColorUniform =
			glGetUniformLocation(m_program, "lightColor");
		//Specular variables
		int eyePosUniform =
			glGetUniformLocation(m_program, "eyePos");
		int specularPowerUniform =
			glGetUniformLocation(m_program, "specularPower");

		glUniform3fv(ambientUniform, 1, (float*)&m_ambientLight);
		glUniform3fv(lightDirUniform, 1, (float*)&m_lightDir);
		glUniform3fv(lightColorUniform, 1, (float*)&m_lightColor);

		vec3 eyePos = m_flyCamera.m_world[3].xyz;
		glUniform3fv(eyePosUniform, 1, (float*)&eyePos);
		glUniform1f(specularPowerUniform, m_specularPower);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_normalTexture);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_specularTexture);

		int diffuseLocation = glGetUniformLocation(m_program, "diffuseTexture");
		int normalLocation = glGetUniformLocation(m_program, "normalTexture");
		int specularLocation = glGetUniformLocation(m_program, "specularTexture");

		glUniform1i(diffuseLocation, 0);
		glUniform1i(normalLocation, 1);
		glUniform1i(specularLocation, 2);
	}

	glBindVertexArray(m_quad.m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	Gizmos::draw(m_flyCamera.m_projView);

	Application::Draw();
}

void AdvancedTextures::loadTextures()
{
	int width, height, channels;

	unsigned char *data = stbi_load("./textures/rock_diffuse.tga", 
									&width, &height, &channels, STBI_default);
	
	glGenTextures(1, &m_diffuseTexture);
	glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
								   GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);

	data = stbi_load("./textures/rock_normal.tga",
		&width, &height, &channels, STBI_default);

	glGenTextures(1, &m_normalTexture);
	glBindTexture(GL_TEXTURE_2D, m_normalTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);

	data = stbi_load("./textures/rock_specular.tga",
		&width, &height, &channels, STBI_default);

	glGenTextures(1, &m_specularTexture);
	glBindTexture(GL_TEXTURE_2D, m_specularTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	stbi_image_free(data);
}

void AdvancedTextures::GenerateQuat(float a_size)
{
	VertexNormal vertexData[4];

	vertexData[0].position = vec4(-a_size, 0, -a_size, 1);
	vertexData[1].position = vec4(-a_size, 0, a_size, 1);
	vertexData[2].position = vec4(a_size, 0, a_size, 1);
	vertexData[3].position = vec4(a_size, 0, -a_size, 1);

	vertexData[0].normal = vec4(0, 1, 0, 0);
	vertexData[1].normal = vec4(0, 1, 0, 0);
	vertexData[2].normal = vec4(0, 1, 0, 0);
	vertexData[3].normal = vec4(0, 1, 0, 0);

	vertexData[0].tangent = vec4(1, 0, 0, 0);
	vertexData[1].tangent = vec4(1, 0, 0, 0);
	vertexData[2].tangent = vec4(1, 0, 0, 0);
	vertexData[3].tangent = vec4(1, 0, 0, 0);

	vertexData[0].texCoord = vec2(0, 0);
	vertexData[1].texCoord = vec2(0, 1);
	vertexData[2].texCoord = vec2(1, 1);
	vertexData[3].texCoord = vec2(1, 0);

	unsigned int indexData[6] = { 0, 2, 1,
		0, 3, 2 };

	m_quad.m_indexCount = 6;
	glGenVertexArrays(1, &m_quad.m_VAO);

	glGenBuffers(1, &m_quad.m_VBO);
	glGenBuffers(1, &m_quad.m_IBO);

	glBindVertexArray(m_quad.m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_quad.m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexNormal)*4, vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quad.m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*6, indexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //position
	glEnableVertexAttribArray(1); //normal
	glEnableVertexAttribArray(2); //tangent
	glEnableVertexAttribArray(3); //tex coord

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexNormal), 0);	//position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(VertexNormal), (void*)(sizeof(vec4) * 1)); //normal
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(VertexNormal), (void*)(sizeof(vec4) * 2));	//tangent
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexNormal), (void*)(sizeof(vec4) * 3)); //tex coord

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}