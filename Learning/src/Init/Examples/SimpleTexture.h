#pragma once

#include "..\GLProgram.h"

class SimpleTexture : public GLProgram
{
private:
	GLfloat	xrot;
	GLfloat	yrot;
	GLfloat	zrot;

	GLuint texture;
public:
	void Init() override;
	void Draw() override;
};