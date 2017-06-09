#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "hitable.h"
#include "common.h"

//! Abstract Material
class Material
{
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};


//! Matte material
class Lambertian : public Material
{
public:
    Lambertian(const Vec3& a) : albedo(a) {}
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;

private:
    Vec3 albedo;
};

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
{
    Vec3 target = rec.p + rec.normal + randomInUnitSphere();
    scattered = Ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
}

//! Metal
class Metal : public Material
{
public:
    Metal(const Vec3& a) : albedo(a) {}
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;

private:
    Vec3 albedo;
};

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
{
    scattered = Ray(rec.p, reflect(r_in.direction() - r_in.origin(), rec.normal));
    attenuation = albedo;
    return scattered.direction().dot(rec.normal) > 0;
}

#endif // !__MATERIAL_H__
