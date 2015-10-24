#include "TimeStepper.h"

///TODO: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
  vector<Vector3f> currentState = particleSystem->getState();
  vector<Vector3f> deris = particleSystem->evalF(currentState);
  vector<Vector3f> nextState;
  for(int i=0;i<currentState.size();i++){
    Vector3f nextState_i = currentState[i]+stepSize*deris[i];
    nextState.push_back(nextState_i);
  }
  particleSystem->setState(nextState);
}

///TODO: implement Trapzoidal rule here
void Trapezoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
  vector<Vector3f> currentState = particleSystem->getState();
  vector<Vector3f> deris_0 = particleSystem->evalF(currentState);
  vector<Vector3f> nextStep;
  for(int i=0;i<currentState.size();i++){
    Vector3f nextStep_i = currentState[i]+stepSize*deris_0[i];
    nextStep.push_back(nextStep_i);
  }
  vector<Vector3f> deris_1 = particleSystem->evalF(nextStep);
  vector<Vector3f> nextState;
  for(int i=0;i<currentState.size();i++){
    Vector3f nextState_i = currentState[i]+stepSize*0.5*(deris_0[i]+deris_1[i]);
    nextState.push_back(nextState_i);
  }
  particleSystem->setState(nextState);
}
