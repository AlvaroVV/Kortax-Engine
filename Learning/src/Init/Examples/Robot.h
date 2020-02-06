#pragma once
#include "..\GLProgram.h"
class Robot : public GLProgram
{
public:
	void init() override;
	void draw() override;
	void processInput(bool* keys) override;

private:

	float angle = 0.0f;
	float legAngle[2] = { 0.0f, 0.0f };
	float armAngle[2] = { 0.0f, 0.0f };

	GLvoid DrawCube(float xPos, float yPos, float zPos);

	void DrawArm(float xPos, float yPos, float zPos);
	void DrawHead(float xPos, float yPos, float zPos);
	void DrawLeg(float xPos, float yPos, float zPos);
	void DrawBody(float xPos, float yPos, float zPos);
	void DrawRobot(float xPos, float yPos, float zPos);

};

