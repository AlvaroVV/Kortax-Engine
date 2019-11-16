#pragma once

#include "..\GLProgram.h"

class SimpleLight : public GLProgram
{

private:
	BOOL light;	//Light ON / OFF
	BOOL lp;	//L pressed
	BOOL fp;	//F Pressed

	GLfloat xrot;       // X Rotation
	GLfloat yrot;       // Y Rotation
	GLfloat xspeed;     // X Rotation Speed
	GLfloat yspeed;     // Y Rotation Speed
	GLfloat z = -5.0f; // Depth Into The Screen

	GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };                 // Ambient Light Values ( NEW )
	GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };              // Diffuse Light Values ( NEW )
	GLfloat LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f };

	GLuint  filter = 0;                                 // Which Filter To Use
	GLuint  texture[3];                             // Storage for 3 textures

public:
	void init() override;
	void draw() override;
	void processInput(bool* keys) override;

private:
	void _loadTextures();
	
};

