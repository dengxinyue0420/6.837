#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "Hit.h"
#include "Ray.h"
#include "Texture.h"

// TODO: Implement Shade function that uses ambient, diffuse, specular and texture
class Material
{
  public:
    Material(const Vector3f &diffuseColor,
             const Vector3f &specularColor = Vector3f::ZERO, 
             float shininess = 0) :
        _diffuseColor(diffuseColor),
        _specularColor(specularColor), 
        _shininess(shininess)
    {
    }

    virtual ~Material()
    {
    }

    virtual const Vector3f & getDiffuseColor() const 
    { 
        return _diffuseColor;
    }

    Vector3f shade(const Ray &ray, 
                   const Hit &hit,
                   const Vector3f &dirToLight, 
                   const Vector3f &lightColor) 
    {
        // TODO: implement
        return Vector3f(1, 1, 1); 
    }

    void loadTexture(const std::string &filename)
    {
        _texture.load(filename);
    }

  private:
    Vector3f _diffuseColor;
    Vector3f _specularColor;
    float _shininess;
    Texture _texture;
};

#endif // MATERIAL_H
