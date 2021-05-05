 // SAMPLE_SOLUTION
#pragma once

#include "vec.h"
#include "modelerdraw.h"
#include <FL/gl.h>

class Particle {
 public:
	Particle(Vec3d p, Vec3d v, double l, double m) : pos(p), vel(v), life(l), mass(m) {}
	 Vec3d get_pos() { return pos; }
	Vec3d get_vel() { return vel; }
	 Vec3d get_force() { return force; }
	double get_life() { return life; }
	 double get_mass() { return mass; }

	 void set_pos(Vec3d p) { pos = p; }
	 void set_vel(Vec3d v) { vel = v; }
	 void set_force(Vec3d f) { force = f; }
	 void set_life(double l) { life = l; }
	 void set_mass(double m) { mass = m; }

	 void update(double);
	 void draw();

private:
	 double life;
	double mass;
	 Vec3d pos;
	Vec3d vel;
	 Vec3d force;

 };