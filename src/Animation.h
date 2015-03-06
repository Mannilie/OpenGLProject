#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "Application.h"
#include "Camera.h"
#include "FBXFile.h"
#include "Vertex.h"

#include <thread>
using std::thread;

#include <iostream>

typedef unsigned int GLuint;

class Animation : public Application
{
private:
public:
	unsigned int m_program;
	bool m_fbxLoaded;
	bool m_meshloaded;
	thread processThread;

	std::vector<OpenGLData> m_meshes;
	FBXFile*				m_fbxFile;
	FlyCamera				m_flyCamera;
	float					m_timer;
	float					m_animationSpeed;

	//Lighting variables
	vec3					m_lightDir;
	vec3					m_lightColor;
	vec3					m_ambientLight;
	float					m_specularPower;
	unsigned int			m_diffuseTexture;
	unsigned int			m_normalTexture;
	unsigned int			m_specularTexture;

	Animation();
	~Animation();
	virtual bool startup();
	virtual void shutdown();
	virtual bool update();
	virtual void draw();

	void generateGLMeshes(FBXFile* a_fbxFile);

	void evaluateSkeleton(FBXAnimation* a_anim, FBXSkeleton* a_skele, float a_timer);
	void updateBones(FBXSkeleton* a_skele);

	//Lighting
	void loadTextures();

	//Mesh functions
	void startLoadMeshThread(char* a_fileName);
	void loadFBXMesh(char* a_fileName);

	void initMeshOpenGL();
	void updateMesh();
	void drawMesh();
};

#endif