#include "SimpleLight.h"
#include "..\..\utils\PngResolver.h"


void SimpleLight::init()
{
	_loadTextures();

	glEnable(GL_TEXTURE_2D);                       
	glShadeModel(GL_SMOOTH);                        
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                
	glClearDepth(1.0f);                       
	glEnable(GL_DEPTH_TEST);                      
	glDepthFunc(GL_LEQUAL);                       
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);        

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);             // Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);             // Setup The Diffuse Light

	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);            // Position The Light

	glEnable(GL_LIGHT1);
}

void SimpleLight::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
	glLoadIdentity();        

	glTranslatef(0.0f, 0.0f, z);                      
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);                     
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);  

	glBindTexture(GL_TEXTURE_2D, texture[filter]);              // Select A Texture Based On filter

	glBegin(GL_QUADS);  
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Point 1 (Front)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Point 2 (Front)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Point 3 (Front)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Point 4 (Front)
															  // Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);                  // Normal Pointing Away From Viewer
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Back)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Point 2 (Back)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Point 3 (Back)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Point 4 (Back)
															   // Top Face
	glNormal3f(0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Point 1 (Top)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Point 2 (Top)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Point 3 (Top)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Point 4 (Top)
															  // Bottom Face
	glNormal3f(0.0f, -1.0f, 0.0f);                  // Normal Pointing Down
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Bottom)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Point 2 (Bottom)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Point 3 (Bottom)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Point 4 (Bottom)
															   // Right face
	glNormal3f(1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Point 1 (Right)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Point 2 (Right)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Point 3 (Right)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Point 4 (Right)
															  // Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Left)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Point 2 (Left)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Point 3 (Left)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Point 4 (Left)
	glEnd();

	xrot += xspeed;                             
	yrot += yspeed;                             
	                    
}

void SimpleLight::_loadTextures()
{
	
	PNG::pngInfo info ;
	PNG::LoadPNG("D:/Proyectos/GitHub/Kortax-Engine/resources/bricks.PNG", info);
	int format = 0;

	switch (info.format) {
	case PNG_COLOR_TYPE_RGBA:
		format = GL_RGBA;
		break;
	case PNG_COLOR_TYPE_RGB:
		format = GL_RGB;
		break;
	default:
		printf("Color type %d not supported!\n",
			info.format);
	}

	glGenTextures(3, &texture[0]);

	//GL_NEAREST
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, format, info.width, info.height, 0,
		format, GL_UNSIGNED_BYTE, (GLvoid *)info.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//GL_LINEAR
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, format, info.width, info.height, 0,
		format, GL_UNSIGNED_BYTE, (GLvoid *)info.data);

	//GL_MIPMAP
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, format, info.width, info.height, 0,
		format, GL_UNSIGNED_BYTE, (GLvoid *)info.data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, info.width, info.height, GL_RGB, GL_UNSIGNED_BYTE, info.data);

	free(info.data);

}

void SimpleLight::processInput(bool* keys)
{
	if (keys['L'] && !lp)
	{
		lp = TRUE;
		light = !light;
		if (!light)
		{
			glDisable(GL_LIGHTING);
		}
		else
		{
			glEnable(GL_LIGHTING);
		}
		printf(light ? "Light ON \n" : "LIGHT OFF \n");
	}
	if (!keys['L'])
	{
		lp = FALSE;
	}
	if (keys['F'] && !fp)
	{
		fp = TRUE;
		filter += 1;
		if (filter>2)
		{
			filter = 0;
		}
		printf("Filter Changed -> %i \n" , filter);
	}
	if (!keys['F'])
	{
		fp = FALSE;
	}
	if (keys[VK_PRIOR])
	{
		z -= 0.02f;
	}
	if (keys[VK_NEXT])
	{
		z += 0.02f;
	}
	if (keys[VK_UP])
	{
		xspeed -= 0.01f;
	}
	if (keys[VK_DOWN])
	{
		xspeed += 0.01f;
	}
	if (keys[VK_RIGHT])
	{
		yspeed += 0.01f;
	}
	if (keys[VK_LEFT])
	{
		yspeed -= 0.01f;
	}
}