#include "Transparency.h"

void Transparency::init()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glLightfv(GL_LIGHT0, GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, ballDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, ballPosition);
	glEnable(GL_LIGHT1);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat);

	//Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f,0.0f,0.0f,0.0f);
}

void Transparency::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (angle > 359.9f)
		angle = 0.0f;
	angle += 0.5f;

	glTranslatef(0.0f, 0.0f, -15.0f);

	glLightfv(GL_LIGHT1, GL_POSITION, ballPosition);

	glPushMatrix();
		glColor3f(1.0f,1.0f,0.0f);
		glTranslatef(ballPosition[0], ballPosition[1], ballPosition[2]);
		DrawCube(0.0f,0.0f,0.0f);
	glPopMatrix();

	glPushMatrix();
		glRotatef( angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 6.0f);
		glColor4f(1.0f, 0.2f, 0.2f, 1.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();

	glEnable(GL_BLEND);

	glDepthMask(GL_FALSE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glPushMatrix();
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -6.0f);
		glColor4f(0.0f, 0.5f, 0.5f, 0.3f);
		glScalef(2.0f, 2.0f, 2.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();

	glDepthMask(GL_TRUE);

	glDisable(GL_BLEND);
}

void Transparency::processInput(bool * keys)
{
}

GLvoid Transparency::DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();

	glTranslatef(xPos, yPos, zPos);

	glBegin(GL_POLYGON);
	//top face
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	//front face
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	//right face
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	//left face
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	//bottomface
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	//back
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glEnd();

	glPopMatrix();
}
