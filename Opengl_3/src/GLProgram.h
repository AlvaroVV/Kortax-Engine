#pragma once
#include <GLAD\glad.h>

class GLProgram
{

public:
	virtual ~GLProgram();

	virtual void init() = 0;
	virtual void draw() = 0;

protected:
	unsigned int shaderProgram;

	void useDefaultProgram();
	unsigned int getShaderProgram() const { return shaderProgram; } 

private:
	virtual void _loadDefaultShaderProgram();
};

