#pragma once
#include "../GLProgram.h"
class Projection_Simple :
	public GLProgram
{

public:
	void init() override;
	void draw() override;
	void processInput(bool* keys, int mouseX, int mouseY) override;

private:

	bool m_cpressed = false;
	GLboolean m_usePerspective = GL_TRUE;

	GLvoid _drawCube(float xPos, float yPos, float zPos);
	void _updateProjection();
	void _customFrustrum(float left, float right, float bottom, float top, float nearVal, float farVal);
};

