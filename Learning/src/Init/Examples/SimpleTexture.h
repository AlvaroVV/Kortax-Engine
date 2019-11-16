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
	void init() override;
	void draw() override;
};