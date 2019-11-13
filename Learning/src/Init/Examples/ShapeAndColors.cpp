
#include "ShapeAndColors.h"


void ShapeAndColors::Init()
{
	glShadeModel(GL_SMOOTH);	// Blends colors across polygons and smoothes out lighing

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	//Sets the color when it clears

	//--- Depth Buffer ---
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); //Enables depth testing
	glDepthFunc(GL_LEQUAL);	// Type of depth test

	//Perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Nice perspective calculations

}

void ShapeAndColors::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();
	//Transformamos la matriz MODELVIEW, por lo que alejamos la escena en -z.

	glTranslatef(-1.5f, 0.0f, -6.0f); //Move MODELVIEW left and into screen
	glRotatef(rtri, 0.0f, 1.0f, 0.0f); //Rotate the pyramid
	glBegin(GL_TRIANGLES);
	//FRONT
	glColor3f(1.0f, 0.0f, 0.0f); //Red
	glVertex3f(0.0f, 1.0f, 0.0f); //top
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(-1.0f, -1.0f, 1.0f); //Left
	glColor3f(0.0f, 0.0f, 1.0f); //Blue
	glVertex3f(1.0f, -1.0f, 1.0f); //Right
								   //RIGHT
	glColor3f(1.0f, 0.0f, 0.0f); //Red
	glVertex3f(0.0f, 1.0f, 0.0f); //top
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(1.0f, -1.0f, 1.0f); //Left
	glColor3f(0.0f, 1.0f, 0.0f); //Green
	glVertex3f(1.0f, -1.0f, -1.0f); //Right
									//BACK
	glColor3f(1.0f, 0.0f, 0.0f); //Red
	glVertex3f(0.0f, 1.0f, 0.0f); //top
	glColor3f(0.0f, 1.0f, 0.0f); //Green
	glVertex3f(1.0f, -1.0f, -1.0f); //Left
	glColor3f(0.0f, 0.0f, 1.0f); //Blue
	glVertex3f(-1.0f, -1.0f, -1.0f); //Right
									 //LEFT
	glColor3f(1.0f, 0.0f, 0.0f); //Red
	glVertex3f(0.0f, 1.0f, 0.0f); //top
	glColor3f(0.0f, 0.0f, 1.0f); //Blue
	glVertex3f(-1.0f, -1.0f, -1.0f); //Left
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(-1.0f, -1.0f, 1.0f); //Right
	glEnd();

	glLoadIdentity();                   // Reset The Current Modelview Matrix
	glTranslatef(1.5f, 0.0f, -7.0f);              // Move Right 1.5 Units And Into The Screen 6.0
	glRotatef(rquad, 1.0f, 1.0f, 1.0f); //Rotate the cube in X,Y,Z

	glBegin(GL_QUADS);
	// Draw A Quad
	//TOP
	glColor3f(0.0f, 1.0f, 0.0f); //Green
	glVertex3f(1.0f, 1.0f, -1.0f);// Top Right
	glVertex3f(-1.0f, 1.0f, -1.0f);// Top Left
	glVertex3f(-1.0f, 1.0f, 1.0f);// Bottom Left
	glVertex3f(1.0f, 1.0f, 1.0f);// Bottom RIght
								 //BOT
	glColor3f(1.0f, 0.5f, 0.0f); //Orange
	glVertex3f(1.0f, -1.0f, -1.0f);// Top Right
	glVertex3f(-1.0f, -1.0f, -1.0f);// Top Left
	glVertex3f(-1.0f, -1.0f, 1.0f);// Bottom Left
	glVertex3f(1.0f, -1.0f, 1.0f);// Bottom Right
								  //FRONT
	glColor3f(1.0f, 0.0f, 0.0f); //Red
	glVertex3f(1.0f, 1.0f, 1.0f);// Top RIght
	glVertex3f(-1.0f, 1.0f, 1.0f);// Top Left
	glVertex3f(-1.0f, -1.0f, 1.0f);// Bottom Left
	glVertex3f(1.0f, -1.0f, 1.0f);// Bottom Right
								  //BACK
	glColor3f(1.0f, 1.0f, 0.0f); //Yellow
	glVertex3f(1.0f, 1.0f, -1.0f);// Top Right
	glVertex3f(-1.0f, 1.0f, -1.0f);// Top Left
	glVertex3f(-1.0f, -1.0f, -1.0f);// Bottom Left
	glVertex3f(1.0f, -1.0f, -1.0f);// Bottom Right
								   //RIGHT
	glColor3f(0.0f, 0.0f, 1.0f); //Blue
	glVertex3f(1.0f, 1.0f, -1.0f);// Top Left
	glVertex3f(1.0f, 1.0f, 1.0f);// Top RIght
	glVertex3f(1.0f, -1.0f, 1.0f);// Bottom Right
	glVertex3f(1.0f, -1.0f, -1.0f);// Bottom Left
								   //LEFT
	glColor3f(1.0f, 0.0f, 1.0f); //Violet
	glVertex3f(-1.0f, 1.0f, -1.0f);// Top Left
	glVertex3f(-1.0f, 1.0f, 1.0f);// Top RIght
	glVertex3f(-1.0f, -1.0f, 1.0f);// Bottom Right
	glVertex3f(-1.0f, -1.0f, -1.0f);// Bottom Left
	glEnd();                            // Done Drawing The Quad

	rtri += 0.5f;
	rquad -= 0.5f;
}

