#pragma once
#include "..\GLProgram.h"
class Transparency : public GLProgram
{
public:
	void init() override;
	void draw() override;

private:
	float angle = 0.0f;

	float lightPosition[4] = {0.0f, 0.0f, 1.0f, 0.0f};

	float diffuseLight[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float diffuseMat[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	float ballDiffuse[4] = {0.5f, 0.5f, 0.0f, 1.0f};
	float ballSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float ballPosition[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	GLvoid _drawCube(float xPos, float yPos, float zPos);

};

