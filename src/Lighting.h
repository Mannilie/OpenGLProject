#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "Application.h"
#include "Camera.h"

#include "tiny_obj_loader.h"

struct OpenGLData
{
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int m_indexCount;
};

class Lighting : public Application
{
private:
	unsigned int m_program;
public:
	FlyCamera m_FlyCamera;
	std::vector<OpenGLData> m_glData;
	vec3 m_lightDir;
	vec3 m_lightColor;
	vec3 m_materialColor;
	vec3 m_ambientLight;
	float m_specularPower;

	void createOpenGLBuffers(std::vector<tinyobj::shape_t>& a_shapes);
	void cleanupOpenGLBuffers();
	void reloadShader();

	virtual bool Startup();
	virtual void Shutdown();
	virtual bool Update();
	virtual void Draw();
};

#endif