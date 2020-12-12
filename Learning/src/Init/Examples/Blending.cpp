#include "Blending.h"
#include "..\..\utils\PngResolver.h"

void Blending::init()
{
	_loadTextures();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, m_LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, m_LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, m_LightPosition);            
	glEnable(GL_LIGHT1);

	//glColor4f(1.0f, 1.0f, 1.0f, 0.5f);         // Full Brightness, 50% Alpha 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);       // Blending Function For Translucency Based On Source Alpha Value 
}

void Blending::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, m_z);
	glRotatef(m_xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yrot, 0.0f, 1.0f, 0.0f);

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

	m_xrot += m_xspeed;
	m_yrot += m_yspeed;

}

void Blending::_loadTextures()
{

	PNG::pngInfo info;
	PNG::LoadPNG("D:/Proyectos/GitHub/Kortax-Engine/resources/circle.png", info);
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

void Blending::processInput(bool* keys, int mouseX, int mouseY)
{
	if (keys['L'] && !m_lp)
	{
		m_lp = TRUE;
		m_light = !m_light;
		if (!m_light)
		{
			glDisable(GL_LIGHTING);
		}
		else
		{
			glEnable(GL_LIGHTING);
		}
		printf(m_light ? "Light ON \n" : "LIGHT OFF \n");
	}
	if (!keys['L'])
	{
		m_lp = FALSE;
	}
	if (keys['F'] && !fp)
	{
		fp = TRUE;
		filter += 1;
		if (filter>2)
		{
			filter = 0;
		}
		printf("Filter Changed -> %i \n", filter);
	}
	if (!keys['F'])
	{
		fp = FALSE;
	}
	if (keys[VK_PRIOR])
	{
		m_z -= 0.02f;
	}
	if (keys[VK_NEXT])
	{
		m_z += 0.02f;
	}
	if (keys[VK_UP])
	{
		m_xspeed -= 0.01f;
	}
	if (keys[VK_DOWN])
	{
		m_xspeed += 0.01f;
	}
	if (keys[VK_RIGHT])
	{
		m_yspeed += 0.01f;
	}
	if (keys[VK_LEFT])
	{
		m_yspeed -= 0.01f;
	}
	if (keys['B'] && !bp)               // Is B Key Pressed And bp FALSE?
	{
		bp = TRUE;                // If So, bp Becomes TRUE
		blend = !blend;             // Toggle blend TRUE / FALSE   
		if (blend)               // Is blend TRUE?
		{
			glEnable(GL_BLEND);     // Turn Blending On
			//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
		}
		else                    // Otherwise
		{
			glDisable(GL_BLEND);        // Turn Blending Off
			//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
		}
		printf("Blending Changed -> %i \n", blend);
	}
	if (!keys['B'])                 // Has B Key Been Released?
	{
		bp = FALSE;               // If So, bp Becomes FALSE
	}
}

