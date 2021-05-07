#pragma warning(disable : 4786)

#include "particleSystem.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <ctime>

/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() 
{
	// TODO

}





/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO
	clearBaked();
}


/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
    
	// TODO

	// These values are used by the UI ...
	// -ve bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	bake_end_time = -1;
	simulate = true;
	dirty = true;
	last_update = t;
}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

void ParticleSystem::add_par(Particle* p) { par.push_back(*p); }

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{

	// TODO
	//printf("curr_time: %f\n", t);
	if (simulate) {
		map<double, vector<Particle>>::iterator itr = cached_par.find(t);
		if (itr != cached_par.end()) {
			par = (*itr).second;
		} else {
			bake_fps = t - last_update;
			vector<int> delete_list;
			for (int i = 0; i < par.size(); ++i) {


				par[i].update(bake_fps);
				if (par[i].get_life() <= 0) {
					delete_list.push_back(i);
				}
			}
			for (int i = delete_list.size() - 1; i >= 0; --i) {
				par.erase(par.begin() + delete_list[i]);
			}
	
			bakeParticles(t);
		}
		last_update = t;
	}
}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{

	// TODO
	if (simulate) {
		for (auto& p : par) {
			p.draw();
		}
	}
}





/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{

	// TODO
	pair<double, vector<Particle>> temp((double)t, par);
	cached_par.insert(temp);
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{

	// TODO
	cached_par.clear();
}





