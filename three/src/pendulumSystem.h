#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H

#include "extra.h"
#include <vector>
#include <math.h> 

#include "particleSystem.h"

class PendulumSystem: public ParticleSystem
{
 public:
	PendulumSystem(int numParticles);
	
	vector<Vector3f> evalF(vector<Vector3f> state);
	void toggleRender(){};
	void toggleMove(){};
	void draw();
 private:
	vector<Vector3f> getPosition(vector<Vector3f> state);
	vector<Vector3f> getVelocity(vector<Vector3f> state);
	Vector3f computeGravity(float m);
	Vector3f computeDrag(float k, Vector3f v);
	Vector3f computeSpring(float k, float r, int i, int j, vector<Vector3f> positions);
};

#endif
