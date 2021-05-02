#pragma once
#include <stdio.h>
#include <math.h>
#include <vector>
#include "vec.h"

typedef struct
{
	Vec3d pos;

	Vec3d normal;

	double flux;
	bool inside;
} Vertex;

typedef struct
{
	Vec3d pos;

	double power;
} Metapoint;

class Metaballs
{
public:

	Metaballs(int);

	void set_iso_value(double);

	void set_ball(int , double , double , double );
	
	Vertex interpolate(Vertex , Vertex );
	
	double get_Vertex_value(Vertex );

private:

	double iso_value;

	Vec3d length;
	
	vector<Metapoint> mtpoint;
};
