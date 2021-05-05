 // SAMPLE_SOLUTION
#include "particle.h"

#define G 9.81
#define k 0.1
#define Ground_dir Vec3d(0,-1,0)
#define p_size 2

void Particle::update(double dt) {
	vel += force / mass * dt;
	pos += vel * dt;
	force = force - k * vel + Ground_dir * mass * G;
	life -= dt;
}

void Particle::draw() { 
	setDiffuseColor(1, 0, 1);
	glPushMatrix();
	glPointSize(p_size);
	glBegin(GL_POINTS);
	glVertex3d(pos[0], pos[1], pos[2]);
	glEnd();
	glPopMatrix();
}