#pragma once

#include "..\GLProgram.h"

class PlaneView :
	public GLProgram
{

public:
	void init() override;
	void draw() override;

	void processInput(bool* keys) override;
	

private:
	void changeView(GLfloat planeX, GLfloat planeY, GLfloat planeZ, GLfloat roll, GLfloat pitch, GLfloat yaw);

	GLfloat roll, pitch, yaw = 0.0f;
	GLfloat posX, posY, posZ = 0.0f;
};

