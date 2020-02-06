#include "WorldExample.h"


void WorldExample::SetupWorld()
{
	FILE *f;
	char oneline[255];
	float x, y, z, u, v;
	float numTriangles;

	fopen_s(&f, "D:/Proyectos/GitHub/Kortax-Engine/resources/World.txt", "r");
	readstr(f, oneline);
	sscanf_s(oneline, "NUMPOLLIES %f\n", &numTriangles);

	sector1.triangles = new TRIANGLE[numTriangles];
	sector1.numTriangles = numTriangles;

	for (int tri = 0; tri < numTriangles; ++tri)
	{
		for (int ver = 0; ver < 3; ++ver)
		{
			readstr(f, oneline);
			sscanf_s(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
			sector1.triangles[tri].vertex[ver].x = x;
			sector1.triangles[tri].vertex[ver].y = y;
			sector1.triangles[tri].vertex[ver].z = z;
			sector1.triangles[tri].vertex[ver].u = u;
			sector1.triangles[tri].vertex[ver].v = v;
		}
	}

	fclose(f);

}

void WorldExample::readstr(FILE* f, char * string)
{

	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}


void WorldExample::init()
{
	idTexture = _loadPNGTexture("D:/Proyectos/GitHub/Kortax-Engine/resources/bricks.PNG");

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set The Blending Function For Translucency
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// This Will Clear The Background Color To Black
	glClearDepth(1.0);									// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glShadeModel(GL_SMOOTH);							// Enables Smooth Color Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	SetupWorld();
}

void WorldExample::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	GLfloat l_x, l_y, l_z, l_u, l_v;
	GLfloat ztrans = -zpos;
	GLfloat sceneroty = -yrot;

	int numtriangles;

	glTranslatef(0.0f, -0.5f, 0.0f);

	glRotatef(lookupdown, 1.0f, 0.0f, 0.0f);
	glRotatef(sceneroty, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, ztrans);

	glBindTexture(GL_TEXTURE_2D, idTexture);

	numtriangles = sector1.numTriangles;

	for (int tri= 0; tri < numtriangles; ++tri)
	{
		glBegin(GL_TRIANGLES);
		glNormal3f( 0.0f, 0.0f, 1.0f );

		for (int ver = 0; ver < 3; ++ver)
		{
			l_x = sector1.triangles[tri].vertex[ver].x;
			l_y = sector1.triangles[tri].vertex[ver].y;
			l_z = sector1.triangles[tri].vertex[ver].z;
			l_u = sector1.triangles[tri].vertex[ver].u;
			l_v = sector1.triangles[tri].vertex[ver].v;
			glTexCoord2f(l_u, l_v); glVertex3f(l_x, l_y, l_z);
		}
		glEnd();
	}
}

void WorldExample::processInput(bool * keys)
{
	if (keys[VK_RIGHT])
	{
		yrot -= 1.2;
	}

	if (keys[VK_LEFT])
	{
		yrot += 1.2f;
	}

	if (keys[VK_UP])
	{
		zpos -= 0.2f;
	}

	if (keys[VK_DOWN])
	{
		zpos += 0.2f;
	}

	if (keys[VK_PRIOR])
	{
		lookupdown -= 1.0f;
	}

	if (keys[VK_NEXT])
	{
		lookupdown += 1.0f;
	}
}
