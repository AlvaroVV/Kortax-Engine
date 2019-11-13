#include "GLProgram.h"

#include "..\utils\PngResolver.h"



void GLProgram::Init()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);	// Blends colors across polygons and smoothes out lighing

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	//Sets the color when it clears

											//--- Depth Buffer ---
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); //Enables depth testing
	glDepthFunc(GL_LEQUAL);	// Type of depth test
							// ----------

							//Perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Nice perspective calculations
}

void GLProgram::Draw()
{
}


GLuint GLProgram::LoadPNGTexture(const char* fileName)
{
	GLuint tex;
	PNG::pngInfo info;
	PNG::LoadPNG(fileName, info);
	int format = 0;

	if (!info.data)
		return 0;

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
		return false;
	}

	glGenTextures(1, &tex);
	//Bindeamos el texture object
	glBindTexture(GL_TEXTURE_2D, tex);

	int align;
	if (!(info.width & 3)) {
		align = 4;
	}
	else if (!info.width & 1) {
		align = 2;
	}
	else {
		align = 1;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, align);
	//Cargamos la imagen
	glTexImage2D(GL_TEXTURE_2D, 0, format, info.width, info.height, 0,
		format, GL_UNSIGNED_BYTE, (GLvoid *)info.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Liberamos espacio
	free(info.data);

	return tex;
}

