#pragma once

#include "..\GLProgram.h"

class ShapeAndColors : public GLProgram
{
private:
	float rtri = 0.0f;
	float rquad = 0.0f;

public:
	void init() override;
	void draw() override;

};