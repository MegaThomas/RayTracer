#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "typeDef.h"
#include "hitable.h"

class Sphere : public Hitable
{
public:
    Sphere() {}
    Sphere(Vec3 center, real radius) : center(center), radius(radius) {}
    ~Sphere() {}

    virtual bool hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const;

private:
    Vec3 center;
    real radius;
};

bool Sphere::hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const
{
    Vec3& A = r.origin();
    Vec3& B = r.direction();
    Vec3 oc = A - center;
    real a = B.squared_norm2(); //< a
    real b = B.dot(oc);         //< b/2
    real c = oc.squared_norm2() - radius*radius;
    real disc = b*b - a*c;
    real root;
    if (disc > 0.0)
    {
        root = (-b - sqrt(disc)) / a;
        if (root < t_max && root > t_min)
        {
            rec.t = root;
            rec.p = r.point_at_parameter(root);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        root = (-b + sqrt(disc)) / a;
        if (root < t_max && root > t_min)
        {
            rec.t = root;
            rec.p = r.point_at_parameter(root);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}

#endif // !__SPHERE_H__

