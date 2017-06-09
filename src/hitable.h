#ifndef __HITABLE_H__
#define __HITABLE_H__

#include "typeDef.h"
#include "ray.h"

class Material;

struct HitRecord
{
    real t;
    Vec3 p;
    Vec3 normal;
    Material *mat;
};

class Hitable
{
public:
    Hitable() {}
    ~Hitable() {}

    virtual bool hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const = 0;
};

#endif // !__HITABLE_H__
