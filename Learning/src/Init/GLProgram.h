#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>


class GLProgram
{
public:
	virtual void init() = 0;
	virtual void draw() = 0;

	//TODO: Ahora mismo virtual pura no se puede. Crear un método virtual vacío de momento y mantener lo comun (Escape y F1) en el main. Context/Window?
	virtual void processInput(bool* keys);

protected:
	GLuint _loadPNGTexture(const char* fileName);
};

