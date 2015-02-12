#include "Utility.h"
#include <cstdio>
#include "gl_core_4_4.h"

bool LoadShaders(char* a_vertShaderFile, char* a_fragShaderFile, GLuint* a_result)
{
	bool loadSucceeded = false;

	FILE* vertFile = fopen(a_vertShaderFile, "r");
	FILE* fragFile = fopen(a_fragShaderFile, "r");

	if (vertFile == 0 || fragFile == 0)
	{
		fclose(vertFile);
		fclose(fragFile);
	}
	else
	{
		fseek(vertFile, 0, SEEK_END);
		int vertFileLength = ftell(vertFile);
		fseek(vertFile, 0, SEEK_SET);

		fseek(fragFile, 0, SEEK_END);
		int fragFileLength = ftell(fragFile);
		fseek(fragFile, 0, SEEK_SET);

		char* vsSource = new char[vertFileLength];
		char* fsSource = new char[fragFileLength];

		vertFileLength = fread(vsSource, 1, vertFileLength, vertFile);
		fragFileLength = fread(fsSource, 1, fragFileLength, fragFile);

		loadSucceeded = true;

		unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertShader, 1, &vsSource, &vertFileLength);
		glCompileShader(vertShader);

		glShaderSource(fragShader, 1, &fsSource, &fragFileLength);
		glCompileShader(fragShader);

		*a_result = glCreateProgram();
		glAttachShader(*a_result, vertShader);
		glAttachShader(*a_result, fragShader);
		glBindAttribLocation(*a_result, 0, "Position");
		glBindAttribLocation(*a_result, 1, "Color");
		glLinkProgram(*a_result);

		//Error checking
		int success = GL_FALSE;
		glGetProgramiv(*a_result, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			int infoLogLength = 0;
			glGetShaderiv(*a_result, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* infoLog = new char[infoLogLength];

			glGetShaderInfoLog(*a_result, infoLogLength, 0, infoLog);
			printf("Error: Failed to link shader program!\n%s\n", infoLog);
			delete[] infoLog;

			loadSucceeded = false;
		}

		glDeleteShader(fragShader);
		glDeleteShader(vertShader);

		delete[] fsSource;
		delete[] vsSource;
	}
	return loadSucceeded;
}