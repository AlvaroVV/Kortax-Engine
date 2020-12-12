#include "C6_Blending.h"



void C6_Blending::init()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPosition);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, m_cubeDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, m_cubeSpecular);
	glEnable(GL_LIGHT1);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuseMat);

	glEnable(GL_COLOR_MATERIAL); //turn on Color Tracking. Allows setting material properties with calls to the glColor*()

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f,0.0f,0.0f,0.0f);
}

void C6_Blending::draw()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	if (m_angle >= 359.9f)
		m_angle = 0.0f;
	m_angle += 1.0f;

	glTranslatef(0.0f,0.0f,-15.0f);

	glLightfv(GL_LIGHT1, GL_POSITION, m_cubePosition);

	glPushMatrix();
		glColor3f(1.0f, 1.0f,0.0f);
		glTranslatef(m_cubePosition[0], m_cubePosition[1], m_cubePosition[2]);
		_drawCube();
	glPopMatrix();

	glPushMatrix();
		glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f,0.0f,6.0f);
		glColor4f(1.0f,0.2f,0.2f,1.0f);
		glScalef(2.0f, 2.0f, 2.0f);
		_drawCube();
	glPopMatrix();

	glEnable(GL_BLEND);

	glDepthMask(GL_FALSE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glPushMatrix();
		glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -6.0f);
		glColor4f(0.0f, 0.5f,0.5f,0.3f);
		glScalef(2.0f, 2.0f, 2.0f);
		_drawCube();
	glPopMatrix();

	glDepthMask(GL_TRUE);

	glDisable(GL_BLEND);
}