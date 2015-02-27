#include "GPUEmitter.h"
#include "GL_Header.h"
#include "Utility.h"

GPUPointEmitter::GPUPointEmitter() :
	m_particles(nullptr), 
	m_maxParticles(0),
	m_position(0),
	m_drawShader(0),
	m_updateShader(0),
	m_lastDrawTime(0)
{
	m_VAO[0] = 0;
	m_VAO[1] = 0;
	m_VBO[0] = 0;
	m_VBO[1] = 0;
}

GPUPointEmitter::~GPUPointEmitter()
{
	delete[] m_particles;
	glDeleteVertexArrays(2, m_VAO);
	glDeleteBuffers(2, m_VAO);
	glDeleteShader(m_updateShader);
	glDeleteShader(m_drawShader);
}

void GPUPointEmitter::init(unsigned int a_maxParticles,
	vec3  a_position,
	float a_emitRate,
	float a_minLifespan,
	float a_maxLifespan,
	float a_minVelocity,
	float a_maxVelocity,
	float a_startSize,
	float a_endSize,
	vec4  a_startColor,
	vec4  a_endColor)
{
	m_maxParticles = a_maxParticles;
	m_position = a_position;
	m_emitRate = a_emitRate;
	m_minLifespan = a_minLifespan;
	m_maxLifespan = a_maxLifespan;
	m_minVelocity = a_minVelocity;
	m_maxVelocity = a_maxVelocity;
	m_startSize = a_startSize;
	m_endSize = a_endSize;
	m_startColor = a_startColor;
	m_endColor = a_endColor;

	m_particles = new GPUParticle[m_maxParticles];
	m_activeBuffer = 0;

	createBuffers();
	createUpdateShader();
	createDrawShader();
}

void GPUPointEmitter::draw(float a_currTime,
	mat4 a_cameraTransform,
	mat4 a_projectionView)
{
	//update vertex pass
	glUseProgram(m_updateShader);
	int deltaUniform 
		= glGetUniformLocation(m_updateShader, "deltaTime");
	int emitterPosUniform
		= glGetUniformLocation(m_updateShader, "emitterPosition");
	int minVelocityUniform
		= glGetUniformLocation(m_updateShader, "minVelocity");
	int maxVelocityUniform
		= glGetUniformLocation(m_updateShader, "maxVelocity");
	int minLifespanUniform
		= glGetUniformLocation(m_updateShader, "minLifespan");
	int maxLifespanUniform
		= glGetUniformLocation(m_updateShader, "maxLifespan");
	int timeUniform
		= glGetUniformLocation(m_updateShader, "time");

	glUniform1f(deltaUniform, a_currTime - m_lastDrawTime);
	glUniform3fv(emitterPosUniform, 1, (float*)&m_position);
	glUniform1f(minVelocityUniform, m_minVelocity);
	glUniform1f(maxVelocityUniform, m_maxVelocity);
	glUniform1f(minLifespanUniform, m_minLifespan);
	glUniform1f(maxLifespanUniform, m_maxLifespan);
	glUniform1f(timeUniform, a_currTime);

	glEnable(GL_RASTERIZER_DISCARD);
	
	glBindVertexArray(m_VAO[m_activeBuffer]);

	unsigned int otherBuffer = (m_activeBuffer + 1) % 2;
	
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_VBO[otherBuffer]);

	glBeginTransformFeedback(GL_POINTS);

	glDrawArrays(GL_POINTS, 0, m_maxParticles);

	glEndTransformFeedback();
	glDisable(GL_RASTERIZER_DISCARD);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);

	//render pass
	glUseProgram(m_drawShader);

	int projViewUniform = glGetUniformLocation(m_drawShader, "projView");
	int cameraWorldUniform = glGetUniformLocation(m_drawShader, "cameraWorld");

	int startSizeUniform = glGetUniformLocation(m_drawShader, "startSize");
	int endSizeUniform = glGetUniformLocation(m_drawShader, "endSize");

	int startColorUniform = glGetUniformLocation(m_drawShader, "startColor");
	int endColorUniform = glGetUniformLocation(m_drawShader, "endColor");

	glUniformMatrix4fv(projViewUniform, 1, GL_FALSE, (float*)&a_projectionView);
	glUniformMatrix4fv(cameraWorldUniform, 1, GL_FALSE, (float*)&a_cameraTransform);

	glUniform1f(startSizeUniform, m_startSize);
	glUniform1f(endSizeUniform, m_endSize);

	glUniform4fv(startColorUniform, 1, (float*)&m_startColor);
	glUniform4fv(endColorUniform, 1, (float*)&m_endColor);

	glBindVertexArray(m_VAO[otherBuffer]);
	glDrawArrays(GL_POINTS, 0, m_maxParticles);

	m_activeBuffer = otherBuffer;

	m_lastDrawTime = a_currTime;
}

void GPUPointEmitter::createBuffers()
{
	glGenVertexArrays(2, m_VAO);
	glGenBuffers(2, m_VBO);

	for (unsigned int bufferIndex = 0; 
		bufferIndex < 2; 
		++bufferIndex)
	{
		glBindVertexArray(m_VAO[bufferIndex]);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[bufferIndex]);

		glBufferData(GL_ARRAY_BUFFER, 
			m_maxParticles * sizeof(GPUParticle), 
			m_particles, GL_STREAM_DRAW);

		glEnableVertexAttribArray(0); //position
		glEnableVertexAttribArray(1); //velocity
		glEnableVertexAttribArray(2); //lifetime
		glEnableVertexAttribArray(3); //lifespan

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
			sizeof(GPUParticle), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
			sizeof(GPUParticle), (void*)(12));
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 
			sizeof(GPUParticle), (void*)(24));
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 
			sizeof(GPUParticle), (void*)(28));
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GPUPointEmitter::createUpdateShader()
{
	unsigned int vertexShader;

	loadShaderType("./shaders/particle_update_vert.glsl", 
		GL_VERTEX_SHADER, 
		&vertexShader);
	
	m_updateShader = glCreateProgram();
	glAttachShader(m_updateShader, vertexShader);

	const char* outputs[4] = { "updatedPosition",
							   "updatedVelocity",
							   "updatedLifetime",
							   "updatedLifespan" };

	glTransformFeedbackVaryings(m_updateShader, 
						4, outputs, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram(m_updateShader);
	glDeleteShader(vertexShader);
}

void GPUPointEmitter::createDrawShader()
{
	loadShaders("./shaders/gpu_particle_vert.glsl",
		"./shaders/gpu_particle_geom.glsl",
		"./shaders/gpu_particle_frag.glsl",
		&m_drawShader);
}