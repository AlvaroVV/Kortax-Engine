#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>


class GLProgram
{
public:
	virtual void Init();
	virtual void Draw();

protected:
	GLuint LoadPNGTexture(const char* fileName);
};

