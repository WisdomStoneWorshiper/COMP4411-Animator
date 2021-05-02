#pragma once
#include "metaballs.h"
#include "vec.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>

class MarchingCube
{
public:
	
	MarchingCube::MarchingCube(Vec3d start, Vec3d end, Vec3d step);

	void drawMarchingCube();

	void calMetaBalls();

	void setStepValue(double);

	void setMetaBalls(Metaballs*, double);
	

private:

	Vec3d start, end, step;
	Vec3i size;

	double metaballs_iso_value;
	void calVertex();

	Metaballs *mb;

	const static int edgeTable[256];
	const static int triTable[256][16];

	Vertex *vertices;

	Vertex verts[12];
};