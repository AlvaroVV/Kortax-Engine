#pragma once
#include "..\..\GLProgram.h"

////--------THEORY------
//Need to be careful with the order in which transparnt objects are drawn due to de DEPTH_TEST.
//One way in doing that, is just making the buffer read-only when transparents are drawn, so need to track them.

class C6_Blending : public GLProgram
{

public:
	void init() override;
	void draw() override;

private:

	float m_angle = 0.0f;

	GLfloat m_lightPosition[4] = { 0.0f, 0.0f, 1.0f, 0.0f }; //Directional light

	GLfloat m_diffuseLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //Diffuse light
	GLfloat m_diffuseMat[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //Diffuse mat 

	GLfloat m_cubeDiffuse[4] = { 0.5f, 0.5f, 0.0f, 1.0f };
	GLfloat m_cubeSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat m_cubePosition[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
};