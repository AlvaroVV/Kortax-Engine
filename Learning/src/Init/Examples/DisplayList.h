#pragma once

#include "..\GLProgram.h"

class DisplayList : public GLProgram
{
private:

	GLuint texture;
	GLuint box;
	GLuint top;
	GLuint xloop;
	GLuint yloop;

	GLfloat xrot;
	GLfloat yrot;

	GLfloat boxcol[5][3] =                                // Array For Box Colors
	{
		// Bright:  Red, Orange, Yellow, Green, Blue
		{ 1.0f,0.0f,0.0f },{ 1.0f,0.5f,0.0f },{ 1.0f,1.0f,0.0f },{ 0.0f,1.0f,0.0f },{ 0.0f,1.0f,1.0f }
	};

	GLfloat topcol[5][3] =                                // Array For Top Colors
	{
		// Dark:  Red, Orange, Yellow, Green, Blue
		{ .5f,0.0f,0.0f },{ 0.5f,0.25f,0.0f },{ 0.5f,0.5f,0.0f },{ 0.0f,0.5f,0.0f },{ 0.0f,0.5f,0.5f }
	};

	GLvoid BuildLists();



public:
	
	void init() override;
	void draw() override;
	void processInput(bool* keys) override;

};

