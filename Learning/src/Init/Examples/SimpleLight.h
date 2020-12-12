#pragma once

#include "..\GLProgram.h"

class SimpleLight : public GLProgram
{

private:
	BOOL m_light;	//Light ON / OFF
	BOOL m_lp;	//L pressed
	BOOL fp;	//F Pressed

	GLfloat m_xrot;       // X Rotation
	GLfloat m_yrot;       // Y Rotation
	GLfloat m_xspeed;     // X Rotation Speed
	GLfloat m_yspeed;     // Y Rotation Speed
	GLfloat m_z = -5.0f; // Depth Into The Screen

	// --- Light Variables
	GLfloat m_LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };               
	GLfloat m_LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat m_LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f }; //Last value means if it's position (1.0) or vector (0.0f), which would be used for directional light.

	// --- Material Variables
	GLfloat m_matAmbient[4] = {1.0f,1.0f,1.0f,1.0f}; // RGB Value reflected by surfaces. 1.0 is fully reflected
	GLfloat m_matDiffuse[4] = { 1.0f,1.0f,1.0f,1.0f };

	GLuint  filter = 0;                                 // Which Filter To Use
	GLuint  texture[3];                             // Storage for 3 textures

public:
	void init() override;
	void draw() override;
	void processInput(bool* keys, int mouseX, int mouseY) override;

private:
	void _loadTextures();
	
};

