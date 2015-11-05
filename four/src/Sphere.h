#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"

#include <vecmath.h>
#include <cmath>

// TODO:
// Implement functions and add more fields as necessary
class Sphere : public Object3D
{
 public:
    Sphere(): 
      _center(Vector3f::ZERO),
      _radius(1.0f)
    { 
    }

    Sphere(const Vector3f &center, 
           float radius, 
           Material *material) :
      Object3D(material),
	_center(center),
	_radius(radius)
    {
    }

    virtual bool intersect(const Ray &r, float tmin, Hit &h) const
    {
      Vector3f origin = r.getOrigin();  
      Vector3f dir = r.getDirection();
      
      float b = 2*(Vector3f::dot(origin,dir)-Vector3f::dot(dir,_center));
      float c = origin.absSquared()-2*Vector3f::dot(origin,_center)+_center.absSquared()-_radius*_radius;
      
      float dis = b*b-4*c;
      if(dis<0){
	return false;  // TODO: implement
      }else if(dis==0){
	float t = -b/2;
	if(t>=tmin&&t<h.getT()){
	  Vector3f interP = r.pointAtParameter(t);
	  Vector3f n = (interP-_center).normalized();
	  h.set(t,this->getMaterial(),n);
	}
      }else{
	float t1 = (-b+std::sqrt(dis))/2;
	float t2 = (-b-std::sqrt(dis))/2;
	float t;
	if(t1>=tmin&&t2>=tmin){
	  if(t1>=t2) t=t2;
	  else t=t1;
	}else if(t1>=tmin){
	  t=t1;
	}else if(t2>=tmin){
	  t=t2;
	}else{
	  return false;
	}
	if(t<h.getT()){
	  Vector3f interP = r.pointAtParameter(t);
	  Vector3f n = (interP-_center).normalized();
	  h.set(t,this->getMaterial(),n);
	}else{
	  return false;
	}
      }
      return true;
    }

  private:
    Vector3f _center;
    float _radius;
};

#endif
