#ifndef _TEXTURING_H_
#define _TEXTURING_H_

#include "Application.h"
#include "Camera.h"

class Texturing : public Application
{
private:
	FlyCamera m_Camera;
	unsigned int m_program;
	unsigned int m_indexCount;
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_texture;
public:
	virtual bool Startup();
	virtual void Shutdown();
	virtual bool Update();
	virtual void Draw();

	void loadTexture(const char* a_filename);
	void GenerateQuat(float a_size);
};

#endif