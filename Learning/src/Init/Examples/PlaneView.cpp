#include "PlaneView.h"

void PlaneView::init()
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

void PlaneView::draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();
	//Transformamos la matriz MODELVIEW, por lo que alejamos la escena en -z.

	
	changeView(posX, posY, posZ, roll, pitch, yaw);
	glBegin(GL_QUADS);
	// Draw A Quad
	 //FRONT
	glColor3f(1.0f, 0.0f, 0.0f); //Red
	glVertex3f(1.0f, 1.0f, -6.0f);// Top RIght
	glVertex3f(-1.0f, 1.0f, -6.0f);// Top Left
	glVertex3f(-1.0f, -1.0f, -6.0f);// Bottom Left
	glVertex3f(1.0f, -1.0f, -6.0f);// Bottom Right
    


	glColor3f(0.0f, 1.0f, 0.0f); //Green
	glVertex3f(6.0f, 1.0f, -1.0f);// Top RIght
	glVertex3f(6.0f, 1.0f, 1.0f);// Top Left
	glVertex3f(6.0f, -1.0f, 1.0f);// Bottom Left
	glVertex3f(6.0f, -1.0f, -1.0f);// Bottom Right

	glColor3f(0.0f, 0.0f, 1.0f); //Blue
	glVertex3f(-1.0f, 1.0f, 6.0f);// Top RIght
	glVertex3f(1.0f, 1.0f, 6.0f);// Top Left
	glVertex3f(1.0f, -1.0f, 6.0f);// Bottom Left
	glVertex3f(-1.0f, -1.0f, 6.0f);// Bottom Right

	glColor3f(1.0f, 1.0f, 0.0f); //Yellow
	glVertex3f(-6.0f, 1.0f, -1.0f);// Top RIght
	glVertex3f(-6.0f, 1.0f, 1.0f);// Top Left
	glVertex3f(-6.0f, -1.0f, 1.0f);// Bottom Left
	glVertex3f(-6.0f, -1.0f, -1.0f);// Bottom Right
	glEnd();

}

void PlaneView::processInput(bool* keys)
{
	if (keys['W'] )               // Is T Being Pressed And Is tp FALSE
	{
		posZ -= 0.1f;
	}
	if (keys['S'])                 // Has The T Key Been Released
	{
		posZ += 0.1f;              // If So, make tp FALSE
	}
	if (keys['A'])                // Is Up Arrow Being Pressed
	{
		posX -= 0.1f;             // Tilt The Screen Up
	}

	if (keys['D'])              // Is Down Arrow Being Pressed
	{
		posX += 0.1f;              // Tilt The Screen Down
	}

	if (keys['Q'])             // Is Page Up Being Pressed
	{
		posY -= 0.1f;             // Zoom Out
	}

	if (keys['E'])              // Is Page Down Being Pressed
	{
		posY += 0.1f;             // Zoom In
	}

	if (keys['J'])              // Is Page Down Being Pressed
	{
		yaw += 0.5f;             // Zoom In
	}

	if (keys['L'])              // Is Page Down Being Pressed
	{
		yaw -= 0.5f;             // Zoom In
	}

	if (keys['I'])              // Is Page Down Being Pressed
	{
		pitch += 0.5f;             // Zoom In
	}

	if (keys['K'])              // Is Page Down Being Pressed
	{
		pitch -= 0.5f;             // Zoom In
	}

	if (keys['U'])              // Is Page Down Being Pressed
	{
		roll -= 0.5f;             // Zoom In
	}

	if (keys['O'])              // Is Page Down Being Pressed
	{
		roll += 0.5f;             // Zoom In
	}
}

void PlaneView::changeView(GLfloat planeX, GLfloat planeY, GLfloat planeZ, GLfloat roll, GLfloat pitch, GLfloat yaw)
{
	glRotatef(roll, 0.0f, 0.0f, 1.0f);
	glRotatef(yaw, 0.0f, 1.0f, 0.0f);
	glRotatef(pitch, 1.0f, 0.0f, 0.0f);

	glTranslatef(-planeX, -planeY, -planeZ);
}
