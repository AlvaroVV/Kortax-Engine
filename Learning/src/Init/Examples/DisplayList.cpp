#include "DisplayList.h"


GLvoid DisplayList::BuildLists()
{
	box = glGenLists(2);

	glNewList(box, GL_COMPILE);

	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
																   // Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
																  // Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
																   // Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
																  // Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glEnd();                                // Done Drawing Quads

	glEndList();

	top = box + 1; //next pointer
	glNewList(top, GL_COMPILE);
	glBegin(GL_QUADS);                          // Start Drawing Quad
												// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glEnd();

	glEndList();
}

void DisplayList::init()
{

	texture = _loadPNGTexture("D:/Proyectos/GitHub/Kortax-Engine/resources/bricks.PNG");
	BuildLists();
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_LIGHT0);                                // Quick And Dirty Lighting (Assumes Light0 Is Set Up)
	glEnable(GL_LIGHTING);                              // Enable Lighting
	glEnable(GL_COLOR_MATERIAL);                            // Enable Material Coloring
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DisplayList::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

	glBindTexture(GL_TEXTURE_2D, texture);
	for (yloop = 1; yloop<6; yloop++)
	{
		for (xloop = 0; xloop<yloop; xloop++)
		{
			glLoadIdentity();							// Reset The View
			glTranslatef(1.4f + (float(xloop)*2.8f) - (float(yloop)*1.4f), ((6.0f - float(yloop))*2.4f) - 7.0f, -20.0f);
			glRotatef(45.0f - (2.0f*yloop) + m_xrot, 1.0f, 0.0f, 0.0f);
			glRotatef(45.0f + m_yrot, 0.0f, 1.0f, 0.0f);
			glColor3fv(boxcol[yloop - 1]);
			glCallList(box);
			glColor3fv(topcol[yloop - 1]);
			glCallList(top);
		}
	}
}

void DisplayList::processInput(bool * keys, int mouseX, int mouseY)
{
	if (keys[VK_LEFT])
	{
		m_yrot -= 0.2f;
	}
	if (keys[VK_RIGHT])
	{
		m_yrot += 0.2f;
	}
	if (keys[VK_UP])
	{
		m_xrot -= 0.2f;
	}
	if (keys[VK_DOWN])
	{
		m_xrot += 0.2f;
	}
}
