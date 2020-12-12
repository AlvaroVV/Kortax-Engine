#pragma once
#include "..\GLProgram.h"

class Blending :
	public GLProgram
{
	BOOL m_light;	//Light ON / OFF
	BOOL blend; //BLend ON / OFF
	BOOL m_lp;	//L pressed
	BOOL fp;	//F Pressed
	BOOL bp;	//B Pressed

	GLfloat m_xrot;       // X Rotation
	GLfloat m_yrot;       // Y Rotation
	GLfloat m_xspeed;     // X Rotation Speed
	GLfloat m_yspeed;     // Y Rotation Speed
	GLfloat m_z = -5.0f; // Depth Into The Screen

	GLfloat m_LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };                 // Ambient Light Values ( NEW )
	GLfloat m_LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };              // Diffuse Light Values ( NEW )
	GLfloat m_LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f };

	GLuint  filter = 0;                                 // Which Filter To Use
	GLuint  texture[3];                             // Storage for 3 textures

public:
	void init() override;
	void draw() override;
	void processInput(bool* keys, int mouseX, int mouseY) override;

private:
	void _loadTextures();
};

