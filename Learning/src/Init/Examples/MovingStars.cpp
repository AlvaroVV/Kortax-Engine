#include "MovingStars.h"
#include "..\..\utils\PngResolver.h"

void MovingStars::init()
{

	texture[0] = _loadPNGTexture("D:/Proyectos/GitHub/Kortax-Engine/resources/leaf.png");

	glEnable(GL_TEXTURE_2D);                // Enable Texture Mapping
	glShadeModel(GL_SMOOTH);                // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);           // Black Background
	glClearDepth(1.0f);                 // Depth Buffer Setup
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
	
	glEnable(GL_DEPTH_TEST); //Enables depth testing
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);           // Set The Blending Function For Translucency
	//glEnable(GL_BLEND);

	for (loop = 0; loop<NUM; loop++)               // Create A Loop That Goes Through All The Stars
	{
		stars[loop].angle = 45.0f;              // Start All The Stars At Angle Zero
		stars[loop].dist = (float(loop) / NUM)*5.0f;     // Calculate Distance From The Center
		stars[loop].r = rand() % 256;            // Give star[loop] A Random Red Intensity
		stars[loop].g = rand() % 256;            // Give star[loop] A Random Green Intensity
		stars[loop].b = rand() % 256;            // Give star[loop] A Random Blue Intensity
	}
	
}

void drawStar()
{
	glBegin(GL_QUADS);          // Begin Drawing The Textured Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();                // Done Drawing The Textured Quad
}

void drawCube()
{
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
	glEnd();
}

void MovingStars::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
	glBindTexture(GL_TEXTURE_2D, texture[0]);       // Select Our Texture
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, zoom);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	drawCube();
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, zoom);
	glTranslatef(5.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	drawCube();
	/*
	for (loop = 0; loop < NUM; loop++)               // Loop Through All The Stars
	{
		glLoadIdentity();               // Reset The View Before We Draw Each Star
		glTranslatef(0.0f, 0.0f, zoom);           // Zoom Into The Screen (Using The Value In 'zoom')
		glRotatef(tilt, 1.0f, 0.0f, 0.0f);         // Tilt The View (Using The Value In 'tilt')
		glRotatef(yspeed, 0.0f, 1.0f, 0.0f);

		glRotatef(stars[loop].angle, 0.0f, 1.0f, 0.0f); // Rotate To The Current Stars Angle
		glTranslatef(stars[loop].dist, 0.0f, 0.0f);    // Move Forward On The X Plane
		glRotatef(-stars[loop].angle, 0.0f, 1.0f, 0.0f);    // Cancel The Current Stars Angle
		glRotatef(-tilt, 1.0f, 0.0f, 0.0f);        // Cancel The Screen Tilt
		drawCube();
		/*
		if (twinkle)                    // Twinkling Stars Enabled
		{
			// Assign A Color Using Bytes
			glColor4ub(stars[(NUM - loop) - 1].r, stars[(NUM - loop) - 1].g, stars[(NUM - loop) - 1].b, 255);
			glBegin(GL_QUADS);          // Begin Drawing The Textured Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();                // Done Drawing The Textured Quad
		}
		*/

		/*
		glRotatef(spin, 0.0f, 0.0f, 1.0f);         // Rotate The Star On The Z Axis
												   // Assign A Color Using Bytes
		glColor4ub(stars[loop].r, stars[loop].g, stars[loop].b, 255);
		glBegin(GL_QUADS);              // Begin Drawing The Textured Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();                    // Done Drawing The Textured Quad

		spin += 0.01f;                    // Used To Spin The Stars
		stars[loop].angle += float(loop) / NUM;      // Changes The Angle Of A Star
		stars[loop].dist -= 0.01f;             // Changes The Distance Of A Star

		if (stars[loop].dist<0.0f)            // Is The Star In The Middle Yet
		{
			stars[loop].dist += 5.0f;          // Move The Star 5 Units From The Center
			stars[loop].r = rand() % 256;        // Give It A New Red Value
			stars[loop].g = rand() % 256;        // Give It A New Green Value
			stars[loop].b = rand() % 256;        // Give It A New Blue Value
		}
	}
		*/
	
}

void MovingStars::processInput(bool* keys)
{
	if (keys['T'] && !tp)               // Is T Being Pressed And Is tp FALSE
	{
		tp = TRUE;                // If So, Make tp TRUE
		twinkle = !twinkle;           // Make twinkle Equal The Opposite Of What It Is
		printf(twinkle ? "Twinkle activated \n" : "Twinkle disabled \n");
	}
	if (!keys['T'])                 // Has The T Key Been Released
	{
		tp = FALSE;               // If So, make tp FALSE
	}
	if (keys[VK_UP])                // Is Up Arrow Being Pressed
	{
		tilt -= 0.5f;             // Tilt The Screen Up
	}

	if (keys[VK_DOWN])              // Is Down Arrow Being Pressed
	{
		tilt += 0.5f;             // Tilt The Screen Down
	}

	if (keys[VK_PRIOR])             // Is Page Up Being Pressed
	{
		zoom -= 0.2f;             // Zoom Out
	}

	if (keys[VK_NEXT])              // Is Page Down Being Pressed
	{
		zoom += 0.2f;             // Zoom In
	}
	if (keys[VK_RIGHT])
	{
		yspeed += 0.2f;
	}
	if (keys[VK_LEFT])
	{
		yspeed -= 0.2f;
	}
}