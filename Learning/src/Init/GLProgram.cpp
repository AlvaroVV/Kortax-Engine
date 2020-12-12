#include "GLProgram.h"

#include "..\utils\PngResolver.h"
#include "..\utils\BmpResolver.h"
#include "..\utils\TargaResolver.h"



GLuint GLProgram::_loadPNGTexture(const char* fileName)
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Liberamos espacio
	free(info.data);

	return tex;
}

/*
* TODO: Crear una Facade/Factory para enmascarar el tema de manejar diferentes archivos. 
*
*/
GLuint GLProgram::_loadTGATexture(const char* fileName)
{
	GLuint tex;
	TGA::TGAFILE tgaFile;

	TGA::LoadTGAFile(fileName, &tgaFile);
	glGenTextures(1, &tex);
	//Bindeamos el texture object
	glBindTexture(GL_TEXTURE_2D, tex);

	int align;

	if (!(tgaFile.imageWidth & 3)) {
		align = 4;
	}
	else if (!tgaFile.imageWidth & 1) {
		align = 2;
	}
	else {
		align = 1;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, align);
	//Cargamos la imagen
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tgaFile.imageWidth, tgaFile.imageHeight, 0,
		GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)tgaFile.imageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

GLuint GLProgram::_loadBMPTexture(const char* fileName)
{
	GLuint tex;
	BMP::BITMAPINFOHEADER	bitmapInfoHeader;
	unsigned char*		bitmapData;

	bitmapData = BMP::LoadBitmapFile(fileName, &bitmapInfoHeader);
	glGenTextures(1, &tex);
	//Bindeamos el texture object
	glBindTexture(GL_TEXTURE_2D, tex);

	int align;

	if (!(bitmapInfoHeader.biWidth & 3)) {
		align = 4;
	}
	else if (!bitmapInfoHeader.biWidth & 1) {
		align = 2;
	}
	else {
		align = 1;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, align);
	//Cargamos la imagen
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0,
		GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)bitmapData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

void GLProgram::_saveScreenshot(FILEType type, unsigned char *imageData, int winWidth, int winHeight)
{
	imageData = (unsigned char*)malloc(winWidth*winHeight * 3);
	memset(imageData, 0, winWidth * winHeight * 3);

	glReadPixels(0, 0, winWidth - 1, winHeight - 1, GL_RGB, GL_UNSIGNED_BYTE, imageData);

	//TODO: Mover esto a un filesystem.
	switch (type)
	{
	case BMP:
		BMP::WriteBitmapFile("writeout.bmp", winWidth, winHeight, (unsigned char*)imageData);
		break;
	case TARGA:
		break;
	default:
		break;
	}
	
}

GLvoid GLProgram::_drawCube(float xPos, float yPos, float zPos )
{
	glPushMatrix();

	glTranslatef(xPos, yPos, zPos);

	glBegin(GL_QUADS);
	//top face
	glNormal3f(0.0f,1.0f,0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.0f, 0.0f);
	//front face
	
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	//right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -1.0f);
	//left face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	//bottomface
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	
	//back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
	
	glEnd();
	
	glPopMatrix();
}

void GLProgram::processInput(bool* keys, int mouseX, int mouseY)
{

}

