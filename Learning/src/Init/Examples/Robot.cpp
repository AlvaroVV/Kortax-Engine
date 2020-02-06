#include "Robot.h"


void Robot::init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Robot::draw()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();

	angle += 1.0f;
	if (angle >= 360.0f)
		angle = 0.0f;

	glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -30.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		DrawRobot(0.0f, 0.0f, 0.0f);
	glPopMatrix();
	glFlush();
}

void Robot::processInput(bool * keys)
{
}

GLvoid Robot::DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();

	glTranslatef(xPos, yPos, zPos);

	glBegin(GL_POLYGON);
	//top face
	glVertex3f(0.0f,0.0f,0.0f);
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

void Robot::DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0,4.0,1.0);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(2.0, 2.0, 2.0);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0, 5.0, 1.0);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawBody(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(3.0, 5.0, 2.0);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawRobot(float xPos, float yPos, float zPos)
{
	static bool leg1 = true;
	static bool leg2 = false;

	static bool arm1 = true;
	static bool arm2 = false;

	glPushMatrix();

		glTranslatef(xPos, yPos, zPos);

		//Draw components
		DrawHead(1.0f, 2.0f, 0.0f);
		DrawBody(1.5f, 0.0f, 0.0f);

		glPushMatrix();
		if (arm1)
			armAngle[0] += 1.0f;
		else
			armAngle[0] -= 1.0f;

		if (armAngle[0] >= 15.0f)
			arm1 = false;
		if (armAngle[0] <= -15.0f)
			arm1 = true;

		glTranslatef(0.0f, -0.5f, 0.0f);
		glRotatef(armAngle[0], 1.0f, 0.0f, 0.0f);
		DrawArm(2.5f, 0.f, -0.5f);

	glPopMatrix();

	glPushMatrix();
		if (arm2)
			armAngle[1] += 1.0f;
		else
			armAngle[1] -= 1.0f;

		if (armAngle[1] >= 15.0f)
			arm2 = false;
		if (armAngle[1] <= -15.0f)
			arm2 = true;

		glTranslatef(0.0f, -0.5f, 0.0f);
		glRotatef(armAngle[1], 1.0f, 0.0f, 0.0f);
		DrawArm(-1.5f, 0.0f, -0.5f);
	glPopMatrix();

	glPushMatrix();
		if (leg1)
			legAngle[0] += 1.0f;
		else
			legAngle[0] -= 1.0f;

		if (legAngle[0] >= 15.0f)
			leg1 = false;
		if (legAngle[0] <= -15.0f)
			leg1 = true;
		glTranslatef(0.0f, -0.5f, 0.0f);
		glRotatef(legAngle[0], 1.0f, 0.0f, 0.0f);
		DrawLeg(-0.5f, -5.0f, -0.5f);
	glPopMatrix();

	glPushMatrix();
		if (leg2)
			legAngle[1] += 1.0f;
		else
			legAngle[1] -= 1.0f;

		if (legAngle[1] >= 15.0f)
			leg2 = false;
		if (legAngle[1] <= -15.0f)
			leg2 = true;
		glTranslatef(0.0f, -0.5f, 0.0f);
		glRotatef(legAngle[1], 1.0f, 0.0f, 0.0f);
		DrawLeg(1.5f, -5.0f, -0.5f);
	glPopMatrix();
	glPopMatrix();
}
