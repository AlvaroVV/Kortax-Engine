#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>


class GLProgram
{
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;

protected:
	GLuint LoadPNGTexture(const char* fileName);
};

