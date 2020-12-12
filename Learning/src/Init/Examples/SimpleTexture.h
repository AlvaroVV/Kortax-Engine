#pragma once

#include "..\GLProgram.h"

class SimpleTexture : public GLProgram
{
private:
	GLfloat	m_xrot;
	GLfloat	m_yrot;
	GLfloat	zrot;

	GLuint texture;
public:
	void init() override;
	void draw() override;
};