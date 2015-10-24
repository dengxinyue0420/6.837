
#include "simpleSystem.h"

using namespace std;

SimpleSystem::SimpleSystem()
{
  Vector3f initial = Vector3f(-1,-1,0);
  vector<Vector3f> states;
  states.push_back(initial);
  this->setState(states);
}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> SimpleSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	for(int i=0;i<state.size();i++){
	  Vector3f deri = Vector3f(-state[i].y(),state[i].x(),0);
	  f.push_back(deri);
	}
	return f;
}

// render the system (ie draw the particles)
void SimpleSystem::draw()
{
  vector<Vector3f> current = this->getState();
  for(int i=0;i<current.size();i++){
    Vector3f pos = current[i];//YOUR PARTICLE POSITION		
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2] );
    glutSolidSphere(0.075f,10.0f,10.0f);
    glPopMatrix();
  }
}
