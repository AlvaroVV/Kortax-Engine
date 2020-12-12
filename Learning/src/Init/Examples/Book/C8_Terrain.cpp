#include "C8_Terrain.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <utils\PngResolver.h>

extern GLfloat w_Width;
extern GLfloat w_Height;

C8_Terrain::C8_Terrain()
{
}

C8_Terrain::~C8_Terrain()
{
	//Deleting 3D array
	for (int i = 0; i < MAP_X; ++i)
	{
		for (int j = 0; j < MAP_Z; ++j)
		{
			delete[] m_terrain_3D[i][j];
		}
		delete[] m_terrain_3D[i];
	}

	delete[] m_terrain_3D;

	//Deleting 1D array
	delete[] m_terrain_1D;
}

void C8_Terrain::init()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_TEXTURE_2D);

	glViewport(0, 0, w_Width, w_Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(54.0f, (GLfloat)w_Width / (GLfloat)w_Height, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	PNG::pngInfo terrainInfo;
	PNG::LoadPNG("D:/Proyectos/GitHub/Kortax-Engine/resources/terrain/terrain.png",terrainInfo);
	m_terrainData = terrainInfo.data;

	InitializeTerrain();
	LoadTextures();
}

void C8_Terrain::processInput(bool *keys, int mouseX, int mouseY)
{
	m_mouseX = mouseX;
	m_mouseY = mouseY;

	if (mouseY < 200)
		mouseY = 200;
	if (mouseY > 450)
		mouseY = 450;

	if ((mouseX - m_mouseX) > 0)
		m_angle += 3.0f;
	else if ((mouseX - m_mouseX) < 0)
		m_angle -= 3.0f;


	if (keys[VK_UP])
	{
		m_waterHeight += 0.2f;
	}
	if (keys[VK_DOWN])
	{
		m_waterHeight -= 0.2f;
	}
}

void C8_Terrain::draw()
{

	
	m_radians = float(M_PI  * (m_angle - 90.f)/ 180.0f);

	//calculate camera's position
	m_cameraX = m_lookX + sin(m_radians)*m_mouseY;
	m_cameraZ = m_lookZ + cos(m_radians)*m_mouseY;

	m_cameraY = m_lookY + m_mouseY / 2.0f;

	//calculate the camera look-at coordinates as the center of the terrain
	m_lookX = (MAP_X * MAP_SCALE)/2.0f;
	m_lookY = 150.0f;
	m_lookZ = -(MAP_Z * MAP_SCALE) / 2.0f;

	//clear the screen and depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(m_cameraX, m_cameraY, m_cameraZ, m_lookX, m_lookY, m_lookZ, 0.0, 1.0, 0.0);

	//set the current texture to the land texture
	glBindTexture(GL_TEXTURE_2D, m_land);
	/*
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.5, 0.5, -3.0);
	_drawCube();
	*/
	
	//loop through all the terrains data points. Draw one triangle strip for each set along x axis.
	for (int z = 0; z < MAP_Z - 1; ++z)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < MAP_X - 1; ++x)
		{
			//for each vertex, we calculate the grayscale shade color
			//Set the texture coordinate and draw the vertex
			//0--1
			//  /
			//2--3

			//vertex 0
			glColor3f(m_terrain_3D[x][z][1] / 255.0f, m_terrain_3D[x][z][1] / 255.0f, m_terrain_3D[x][z][1] / 255.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(m_terrain_3D[x][z][0], m_terrain_3D[x][z][1], m_terrain_3D[x][z][2]);

			//vertex 1
			glTexCoord2f(1.0f, 0.0f);
			glColor3f(m_terrain_3D[x + 1][z][1] / 255.0f, m_terrain_3D[x + 1][z][1] / 255.0f, m_terrain_3D[x + 1][z][1] / 255.0f);
			glVertex3f(m_terrain_3D[x + 1][z][0], m_terrain_3D[x + 1][z][1], m_terrain_3D[x + 1][z][2]);

			//vertex 2
			glTexCoord2f(0.0f, 1.0f);
			glColor3f(m_terrain_3D[x][z + 1][1] / 255.0f, m_terrain_3D[x][z + 1][1] / 255.0f, m_terrain_3D[x][z + 1][1] / 255.0f);
			glVertex3f(m_terrain_3D[x][z + 1][0], m_terrain_3D[x][z + 1][1], m_terrain_3D[x][z + 1][2]);

			//vertex 3
			glTexCoord2f(1.0f, 1.0f);
			glColor3f(m_terrain_3D[x + 1][z + 1][1] / 255.0f, m_terrain_3D[x + 1][z + 1][1] / 255.0f, m_terrain_3D[x + 1][z + 1][1] / 255.0f);
			glVertex3f(m_terrain_3D[x + 1][z + 1][0], m_terrain_3D[x + 1][z + 1][1], m_terrain_3D[x + 1][z + 1][2]);
		}
		glEnd();
	}
	
	
	glEnable(GL_BLEND);

	glDepthMask(GL_FALSE);

	//set the blend function to what we use for transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glColor4f(0.5f, 0.5f, 1.0f, 0.7f);		//Transparent color to blue
	glBindTexture(GL_TEXTURE_2D, m_water);	

	//Draw water as one large quad
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_terrain_3D[0][0][0], m_waterHeight, m_terrain_3D[0][0][2]);

		glTexCoord2f(10.0f, 0.0f);
		glVertex3f(m_terrain_3D[MAP_X - 1][0][0], m_waterHeight, m_terrain_3D[MAP_X-1][0][2]);

		glTexCoord2f(10.0f, 10.0f);
		glVertex3f(m_terrain_3D[MAP_X - 1][MAP_Z-1][0], m_waterHeight, m_terrain_3D[MAP_X-1][MAP_Z-1][2]);

		glTexCoord2f(0.0f, 10.0f);
		glVertex3f(m_terrain_3D[0][MAP_Z - 1][0], m_waterHeight, m_terrain_3D[0][MAP_Z- 1][2]);

	glEnd();

	glDepthMask(GL_TRUE);

	glDisable(GL_BLEND);

	if (m_waterHeight > 155.0f)
		m_waterDir = false;
	else if (m_waterHeight < 154.0f)
		m_waterDir = true;

	if (m_waterDir)
		m_waterHeight += 0.01f;
	else
		m_waterHeight -= 0.01f;

		
}


void C8_Terrain::InitializeTerrainArrays()
{
	//C++11
	//auto temp = new float[MAP_X][MAP_Y][3];
	//Move semantics (?)
	
	//3Dimension
	//Using a pointer that points pointers to int points
	m_terrain_3D = new float **[MAP_X];
	for (int i = 0; i < MAP_X; ++i)
	{
		m_terrain_3D[i] = new float*[MAP_Z];
		for (int j = 0; j < MAP_Z; ++j)
		{
			m_terrain_3D[i][j] = new float[3];
		}
	}

	//1Dimension
	//Just calculating throw arithmetic
	m_terrain_1D = new float[MAP_X * MAP_Z * 3];
}

void C8_Terrain::InitializeTerrain()
{
	InitializeTerrainArrays();

	for (int z = 0; z < MAP_Z; ++z)
	{
		for (int x = 0; x < MAP_X; ++x)
		{
			m_terrain_3D[x][z][0] = float(x) * MAP_SCALE;
			m_terrain_3D[x][z][1] = (float) m_terrainData[(z*MAP_Z+x)*3]; //Como es grayscale en el RGB, se multiplica por 3.
			m_terrain_3D[x][z][2] = float(z) * MAP_SCALE * (-1);
		}
	}
}

void C8_Terrain::LoadTextures()
{
	m_land = _loadPNGTexture("D:/Proyectos/GitHub/Kortax-Engine/resources/terrain/land.png");
	m_water = _loadPNGTexture("D:/Proyectos/GitHub/Kortax-Engine/resources/terrain/water.png");
}
