#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"

#include <vecmath.h>
#include <cmath>

// TODO: Implement Plane representing an infinite plane
// Choose your representation, add more fields and fill in the functions
class Plane: public Object3D
{
  public:
    Plane(const Vector3f &normal, float d, Material *m) :
        Object3D(m)
    {
    }

    virtual bool intersect(const Ray &r, float tmin, Hit &h) const 
    {
        return false;  // TODO: implement
    }

 private:
};
#endif //PLANE_H


