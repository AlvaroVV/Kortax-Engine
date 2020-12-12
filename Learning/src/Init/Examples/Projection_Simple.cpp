#include "Projection_Simple.h"

void Projection_Simple::init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Projection_Simple::draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f); //Green
	_drawCube(-0.5f, 0.0f, -5.0f);

	glColor3f(1.0f, 0.0f, 0.0f); //Red
	_drawCube(0.0f, 0.0f, -6.0f);

	glColor3f(0.0f, 0.0f, 1.0f); //Blue
	_drawCube(0.5f, 0.0f, -7.0f);
	
	
}

void Projection_Simple::processInput(bool * keys, int mouseX, int mouseY)
{
	if (keys['C'] && !m_cpressed)
	{
		_customFrustrum(-1.0, 1.0, -1.0, 1.0, 5, 100);
		//_updateProjection();
		m_cpressed = true;
	}
	if (!keys['C'])
		m_cpressed = false;
}

GLvoid Projection_Simple::_drawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();

	glTranslatef(xPos, yPos, zPos);
	glRotatef(45, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	//top face
	glVertex3f(0.0f, 0.0f, 0.0f);
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

void Projection_Simple::_updateProjection()
{
	m_usePerspective = !m_usePerspective;

	//Limpiamos la matriz proyeccion
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();

	//Elegimos proyeccion
	if (m_usePerspective)
		glFrustum(-1.0, 1.0, -1.0, 1.0, 5, 100);
	else
		glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);

	glMatrixMode(GL_MODELVIEW);
	
}

/*---- Custom Frustrum-----
* In Opengl 2d arrays are column major, so it's better to use 1d.
* Theory about this projection: https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/projection-matrices-what-you-need-to-know-first
* Documentation about glFrustrum: https://docs.gl/gl3/glFrustum
*/
void Projection_Simple::_customFrustrum(float left, float right, float bottom, float top, float nearVal, float farVal)
{
	m_usePerspective = !m_usePerspective;

	if (m_usePerspective)
	{
		float A = (right + left) / (right - left);
		float B = (top + bottom) / (top - bottom);
		float C = -((farVal + nearVal) / (farVal - nearVal));
		float D = -((2 * farVal*nearVal) / (farVal - nearVal));

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		static GLfloat frustrum_matrix[16] = { (2 * nearVal) / right - left,0,0,0,
										0,(2 * nearVal) / top - bottom,0,0,
										A,B,C,-1,
										0,0,D,0 };

		glMultMatrixf(frustrum_matrix);
	}
	else
		glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);

	glMatrixMode(GL_MODELVIEW);
}
