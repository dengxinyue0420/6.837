
#include "pendulumSystem.h"

PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	m_numParticles = numParticles;
	this->m_vVecState.push_back(Vector3f(0,0,0));
	this->m_vVecState.push_back(Vector3f(0,0,0));
	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_numParticles-1; i++) {
	  // for this system, we care about the position and the velocity
	  this->m_vVecState.push_back(Vector3f(0,-1,0));
	  this->m_vVecState.push_back(Vector3f(0,-1,0));
	}
}

vector<Vector3f> getPosition(vector<Vector3f> state){
  vector<Vector3f> positions;
  for(int i=0;i<state.size();i+=2){
    Vector3f position_i = state[i];
    positions.push_back(position_i);
  }
  return positions;
}
vector<Vector3f> getVelocity(vector<Vector3f> state){
  vector<Vector3f> vs;
  for(int i=1;i<state.size();i+=2){
    Vector3f v_i = state[i];
    vs.push_back(v_i);
  }
  return vs;
}

Vector3f computeGravity(float m){
  return m*Vector3f(0,-9.8,0);
}
Vector3f computeDrag(float k,Vector3f v){
  return -k*v;
}
Vector3f computeSpring(float k, float r,Vector3f pos_i, Vector3f pos_j){
  Vector3f diff = pos_i-pos_j;
  return -k*(diff.abs()-r)*diff.normalized();
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
  float m = 0.1;
  float kf = 0.5;
  float ks = 0.5;
  float r = 0.8;
  vector<Vector3f> f;
  vector<Vector3f> currentPos = getPosition(state);
  vector<Vector3f> currentVel = getVelocity(state);
  Vector3f fixed = currentPos[0];
  f.push_back(Vector3f::ZERO);
  f.push_back(Vector3f::ZERO);
  for(int i=1;i<m_numParticles;i++){
    f.push_back(currentVel[i]);
    Vector3f force = computeGravity(m)+computeDrag(kf, currentVel[i])+computeSpring(ks,r,currentPos[i],fixed);
    f.push_back(force/m);
  }
  
  return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
  vector<Vector3f> positions = getPosition(this->getState());
  for (int i = 0; i < m_numParticles; i++) {
    Vector3f pos = positions[i];//  position of particle i. YOUR CODE HERE
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2] );
    glutSolidSphere(0.075f,10.0f,10.0f);
    glPopMatrix();
  }
}
