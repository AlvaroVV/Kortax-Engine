#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>



class GLProgram
{
protected:
	enum FILEType
	{
		TARGA,
		BMP,
		PNG
	};

public:
	virtual void init() = 0;
	virtual void draw() = 0;

	//TODO: Ahora mismo virtual pura no se puede. Crear un método virtual vacío de momento y mantener lo comun (Escape y F1) en el main. Context/Window?
	virtual void processInput(bool* keys, int mouseX, int mouseY);

protected:
	//TODO: Facade o Factory para quitar esta funcionalidad de aqui
	//Al final se necesita unsigned char* data, los tamaños y el bitCount.
	//Crear TextureSample class
	GLuint _loadPNGTexture(const char* fileName);
	GLuint _loadBMPTexture(const char* fileName);
	GLuint _loadTGATexture(const char* fileName);

	void _saveScreenshot(FILEType type, unsigned char *imageData, int winWidth, int winHeight);

	GLvoid _drawCube(float xPos=0.0f, float yPos = 0.0f, float zPos = 0.0f);
};

