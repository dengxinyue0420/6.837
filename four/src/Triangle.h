#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

// TODO: implement this class.
class Triangle: public Object3D
{
  public:
    Triangle(const Vector3f &a, 
             const Vector3f &b, 
             const Vector3f &c, 
             const Vector3f &na,
             const Vector3f &nb,
             const Vector3f &nc,
             Material *m) :
        Object3D(m),
        _hasTex(false)
    {
        // TODO: implement
    }

    virtual bool intersect(const Ray &ray, float tmin, Hit &hit) const {
        return false;  // TODO: implement
    }

    void setTex(const Vector2f &uva,
                const Vector2f &uvb,
                const Vector2f &uvc)
    {
        _texCoords[0] = uva;
        _texCoords[1] = uvb;
        _texCoords[2] = uvc;
        _hasTex = true;
    }

    bool hasTex() const {
        return _hasTex;
    }

  private:
    bool _hasTex;
    Vector3f _vertices[3];
    Vector3f _normals[3];
    Vector2f _texCoords[3];
};

#endif //TRIANGLE_H
