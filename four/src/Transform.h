#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Object3D.h"
#include "vecmath.h"

// TODO implement this class
// So that the intersect function first transforms the ray
// Add more fields as necessary
class Transform: public Object3D
{
  public: 
    Transform(const Matrix4f &m, 
              Object3D *obj) :
        _object(obj) 
    {
    }

    virtual bool intersect(const Ray &r, float tmin, Hit &h) const
    {
        return _object->intersect(r, tmin, h);  // TODO: implement correctly
    }

  protected:
    Object3D *_object; //un-transformed object	
};

#endif //TRANSFORM_H
