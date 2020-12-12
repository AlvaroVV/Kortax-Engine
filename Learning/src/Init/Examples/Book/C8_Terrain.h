#pragma once
#include "Init\GLProgram.h"



class C8_Terrain :
	public GLProgram
{

public:

	static const int MAP_X = 32;
	static const int MAP_Z = 32;
	static const int MAP_SCALE = 20;

private:
	float m_angle = 0.0f;
	float m_radians = 0.0f;
	float m_waterHeight = 154.0f;
	bool m_waterDir = true;

	int m_mouseX, m_mouseY;
	float m_cameraX, m_cameraY, m_cameraZ;
	float m_lookX, m_lookY, m_lookZ;

	GLuint m_land;
	GLuint m_water;

	unsigned char*	m_terrainData;

	float ***m_terrain_3D;
	float *m_terrain_1D;

public:
	C8_Terrain();
	~C8_Terrain();

	void init() override;
	void draw() override;

	void processInput(bool *keys, int mouseX, int mouseY) override;

private:
	void InitializeTerrainArrays();

	void InitializeTerrain();
	void LoadTextures();
};

