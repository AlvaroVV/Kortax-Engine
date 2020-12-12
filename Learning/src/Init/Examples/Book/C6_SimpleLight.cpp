#include "C6_SimpleLight.h"
#include <stdio.h>


void C6_SimpleLight::init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);    //Shade smooth                                     
	glEnable(GL_DEPTH_TEST);	//Hidden surfaces removed    
	glEnable(GL_CULL_FACE);		//Don't calculate back faces
	glFrontFace(GL_CCW);		//CCW polys are out. 

	glEnable(GL_LIGHTING);		//Enable Light

	//Ambient Light
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_LightAmbient);             // Setup The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_LightDiffuse);             // Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_POSITION, m_LightPosition);            // Position The Light

	//Spot light properties
	glLightfv(GL_LIGHT1, GL_DIFFUSE, m_LightDiffuse);             
	glLightfv(GL_LIGHT1, GL_AMBIENT, m_LightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION, m_SpotLightPosition);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 30.0f);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, m_SpotLightDirection);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//Material Properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_matDiffuse);
}

void C6_SimpleLight::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
	glLoadIdentity();        

	glTranslatef(0.0f, 0.0f, m_z);                      
	glRotatef(m_xrot, 1.0f, 0.0f, 0.0f);                     
	glRotatef(m_yrot, 0.0f, 1.0f, 0.0f);  

	_drawCube(0.0f,0.0f,0.0f);

	m_xrot += m_xspeed;                             
	m_yrot += m_yspeed;                             
	
}



void C6_SimpleLight::processInput(bool* keys, int mouseX, int mouseY)
{
	if (keys['1'] && !m_pressedAmbient)
	{
		m_pressedAmbient = TRUE;
		m_lightAmbientOn = !m_lightAmbientOn;
		if (!m_lightAmbientOn)
			glDisable(GL_LIGHT0);
		else
			glEnable(GL_LIGHT0);
		printf(m_lightAmbientOn ? "Light-Ambient ON \n" : "Light-Ambient OFF \n");
	}
	if (!keys['1'])
	{
		m_pressedAmbient = FALSE;
	}
	if (keys['2'] && !m_pressedSpot)
	{
		m_pressedSpot = TRUE;
		m_lightSpotOn = !m_lightSpotOn;
		if (!m_lightSpotOn)
			glDisable(GL_LIGHT0);
		else
			glEnable(GL_LIGHT0);
		printf(m_lightSpotOn ? "Light-Spot  ON \n" : "Light-Spot OFF\n");
	}
	if (!keys['2'])
	{
		m_pressedSpot = FALSE;
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
}