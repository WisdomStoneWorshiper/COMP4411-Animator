#include "metaballs.h"

Metaballs::Metaballs(int num_metapoints)
{
	mtpoint.resize(num_metapoints);
	for (int i = 0; i < mtpoint.size(); ++i) {
		mtpoint[i].power = 1.5;
	}
}


void Metaballs::set_iso_value(double iv)
{
	this->iso_value = iv;
}


void Metaballs::set_ball(int idx, double x, double y, double z)
{
	mtpoint[idx].pos[0] = x;
	mtpoint[idx].pos[1] = y;
	mtpoint[idx].pos[2] = z;
}

Vertex Metaballs::interpolate(Vertex v1, Vertex v2)
{
	Vertex v;
	double diff = (this->iso_value - v1.flux) / (v2.flux - v1.flux);

	v.pos[0] = v1.pos[0] + (v2.pos[0] - v1.pos[0]) * diff;
	v.pos[1] = v1.pos[1] + (v2.pos[1] - v1.pos[1]) * diff;
	v.pos[2] = v1.pos[2] + (v2.pos[2] - v1.pos[2]) * diff;
	v.flux = (v1.flux + v2.flux) * 0.5;

	v.normal[0] = v1.normal[0] + (v2.normal[0] - v1.normal[0]) * diff;
	v.normal[1] = v1.normal[1] + (v2.normal[1] - v1.normal[1]) * diff;
	v.normal[2] = v1.normal[2] + (v2.normal[2] - v1.normal[2]) * diff;

	return v;
}


double Metaballs::get_Vertex_value(Vertex v)
{
	double flux = 0.0;

	for (int i = 0; i < mtpoint.size(); i++)
	{

		length[0] = mtpoint[i].pos[0] - v.pos[0];
		length[1] = mtpoint[i].pos[1] - v.pos[1];
		length[2] = mtpoint[i].pos[2] - v.pos[2];

		flux += fabs(mtpoint[i].power) * mtpoint[i].power / (
			length[0] * length[0] +
			length[1] * length[1] +
			length[2] * length[2] + 1);
	}

	return flux;
}