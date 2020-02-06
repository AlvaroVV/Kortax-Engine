#pragma once

#include "..\GLProgram.h"
#include <stdio.h>

class WorldExample: public GLProgram
{

	struct VERTEX
	{
		float x, y, z;
		float u, v;
	};

	struct TRIANGLE
	{
		VERTEX vertex[3];
	};

	struct SECTOR
	{
		int numTriangles;
		TRIANGLE* triangles;
	};


public:
	void init() override;
	void draw() override;
	void processInput(bool* keys) override;


private:
	GLuint idTexture = 0.0f;

	GLfloat yrot = 0.0f;
	GLfloat zpos = 0.0f;
	GLfloat lookupdown = 0.0f;

	SECTOR sector1;

	void SetupWorld();
	void readstr(FILE*, char *string);
};