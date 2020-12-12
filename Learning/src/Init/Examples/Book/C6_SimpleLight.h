#pragma once

#include "..\..\GLProgram.h"

class C6_SimpleLight : public GLProgram
{

private:
	BOOL m_lightAmbientOn = true;	//Ambient Light ON / OFF
	BOOL m_pressedAmbient;	//1 pressed

	BOOL m_lightSpotOn = true;		//SpotLight On /Off
	BOOL m_pressedSpot;		//2 pressed

	GLfloat m_xrot;       // X Rotation
	GLfloat m_yrot;       // Y Rotation
	GLfloat m_xspeed;     // X Rotation Speed
	GLfloat m_yspeed;     // Y Rotation Speed
	GLfloat m_z = -5.0f; // Depth Into The Screen

	// --- Light Variables
	GLfloat m_LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };               
	GLfloat m_LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat m_LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f }; //Last value means if it's position (1.0) or vector (0.0f), which would be used for directional light.
	GLfloat m_SpotLightPosition[4] = { 6.0f, 0.5f, 0.0f, 1.0f };
	GLfloat m_SpotLightDirection[3] = {-1.0,0.0f,-1.0f};

	// --- Material Variables
	GLfloat m_matAmbient[4] = {1.0f,1.0f,1.0f,1.0f}; // RGB Value reflected by surfaces. 1.0 is fully reflected
	GLfloat m_matDiffuse[4] = { 1.0f,1.0f,1.0f,1.0f };

public:
	void init() override;
	void draw() override;
	void processInput(bool* keys, int mouseX, int mouseY) override;


};

