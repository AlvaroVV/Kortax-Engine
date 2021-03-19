#pragma once
#include <GLAD\glad.h>

class GLProgram
{

public:

	GLProgram();
	virtual ~GLProgram();

	virtual void init();
	virtual void draw();


protected:

	unsigned int loadShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);

private:

	unsigned int loadDefaultShaderProgram();

protected:

	unsigned int mDefaultShader;
};

