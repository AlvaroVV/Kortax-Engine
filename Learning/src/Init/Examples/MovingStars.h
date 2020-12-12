#pragma once
#include "..\GLProgram.h"

class MovingStars: public GLProgram
{
private:

	static const int  NUM = 3;
	
	BOOL    twinkle;   // Twinkling Stars
	BOOL    tp;        // 'T' Key Pressed?

	typedef struct
	{
		int r, g, b;
		GLfloat dist;
		GLfloat angle;
	} star;

	star stars[NUM];

	GLfloat zoom = -15.0f;  // Viewing Distance Away From Stars
	GLfloat tilt = 90.0f;  // Tilt The View
	GLfloat m_yspeed = 0.0f;
	GLfloat spin;          // Spin Twinkling Stars

	GLuint  loop = 0;          // General Loop Variable
	GLuint  texture[1];    // Storage For One Texture

public:
	void init() override;
	void draw() override;
	void processInput(bool* keys, int mouseX, int mouseY) override;

};