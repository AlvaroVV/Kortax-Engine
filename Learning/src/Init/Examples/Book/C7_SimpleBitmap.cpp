#include "C7_SimpleBitmap.h"
#include <stdio.h>

extern GLfloat w_Width;
extern GLfloat w_Height;

void C7_SimpleBitmap::init()
{
	glViewport(0.0f, 0.0f,  w_Width, w_Height);
	glMatrixMode(GL_PROJECTION);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glLoadIdentity();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);

	m_texBMP = _loadBMPTexture("D:/Proyectos/GitHub/Kortax-Engine/resources/BMPCheckPattern.bmp");
	m_texPNG = _loadPNGTexture("D:/Proyectos/GitHub/Kortax-Engine/resources/PNGCheckPattern.PNG");
	m_texTarga = _loadTGATexture("D:/Proyectos/GitHub/Kortax-Engine/resources/TGACheckPattern.tga");

	glBindTexture(GL_TEXTURE_2D, m_texTarga);
}

void C7_SimpleBitmap::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	_textureExample();
}


void C7_SimpleBitmap::_simpleBitmap()
{
	glColor3f(1.0f,1.0f,1.0f);

	for (int numA = 0; numA < 50; ++numA)
	{
		glRasterPos2i(rand() % 800, rand()% 600);
		glBitmap(16,16,0.0f,0.0f,0.0f,0.0f,m_letterA);
	}

}

void C7_SimpleBitmap::_textureExample()
{
	
	
	//glTranslatef(0.0f,0.0f,-3.0f);
	glRotatef(m_angle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
	glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
	_drawCube();

	if (m_angle >= 360.0f)
		m_angle = 0.0f;
	m_angle += 0.2f;

}



void C7_SimpleBitmap::processInput(bool* keys, int mouseX, int mouseY)
{
	if (keys['1'] && !m_keyPushed)
	{
		m_keyPushed = TRUE;
		glBindTexture(GL_TEXTURE_2D, m_texPNG);
		printf("PNG ON \n");
		return;
	}
	if (keys['2'] && !m_keyPushed)
	{
		m_keyPushed = TRUE;
		glBindTexture(GL_TEXTURE_2D, m_texTarga);
		printf("TARGA ON \n");
		return;
	}
	if (keys['3'] && !m_keyPushed)
	{
		m_keyPushed = TRUE;
		glBindTexture(GL_TEXTURE_2D, m_texBMP);
		printf("BMP ON \n");
		return;
	}

	//TODO: gestionar 1 pulsacion
	m_keyPushed = FALSE;
}