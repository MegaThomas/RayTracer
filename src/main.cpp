#include <iostream>
#include <fstream>
#include <ctime>
#include "typeDef.h"
#include "common.h"
#include "bmp.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable.h"
#include "hitableList.h"
#include "camera.h"
#include "material.h"


Vec3 color(const Ray& r, Hitable *world, int depth)
{
    HitRecord tempRec;
    if (world->hit(r, 0.001, 1e10, tempRec))
    {
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50 && tempRec.mat->scatter(r, tempRec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return Vec3(0, 0, 0);
        }
    }
    else
    {
        Vec3 unit = r.direction().normalize();
        real t = 0.5*(unit.y() + 1.0);
        return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
    }
}

int main(int argc, char const *argv[])
{

    int nx = 800;
    int ny = 400;
    int ns = 500;
    BMP bitmap(nx, ny);
    Hitable *list[53];
    std::srand(std::time(0));
    list[0] = new Sphere(Vec3(-1.5, 0, -1), 0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vec3(0, -1000.5, -1), 1000, new Lambertian(Vec3(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vec3(1.5, 0, -1), 0.5, new Metal(Vec3(0.8, 0.5, 0.3)));
    for (int i = 0; i < 25; i++)
    {
        real z = -real(std::rand()) * 10 / RAND_MAX - 1;
        real x = real(std::rand()) * 2 * z / RAND_MAX - z;
        real r = real(std::rand()) * 0.25 / RAND_MAX;
        list[3+i] = new Sphere(Vec3(x, -0.5 + r, z), r,
            new Metal(Vec3(real(std::rand()) / RAND_MAX, real(std::rand()) / RAND_MAX, real(std::rand()) / RAND_MAX)));
    }
    for (int i = 0; i < 25; i++)
    {
        real z = -real(std::rand()) * 10 / RAND_MAX - 1;
        real x = real(std::rand()) * 2 * z / RAND_MAX - z;
        real r = real(std::rand()) * 0.25 / RAND_MAX;
        list[28 + i] = new Sphere(Vec3(x, -0.5 + r, z), r,
            new Lambertian(Vec3(real(std::rand()) / RAND_MAX, real(std::rand()) / RAND_MAX, real(std::rand()) / RAND_MAX)));
    }
    /*list[3] = new Sphere(Vec3(-1.5, 0, -1), 0.5, new Metal(Vec3(0.7, 0.7, 0.2)));
    list[4] = new Sphere(Vec3(-0.5, -0.25, -0.4), 0.25, new Metal(Vec3(0.9, 0.8, 0.3)));*/
    Hitable *world = new HitableList(list, 53);
    Camera cam;
    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; ++i)
        {
            Vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                real u = real(i + real(std::rand()) / RAND_MAX) / real(nx);
                real v = real(j + real(std::rand()) / RAND_MAX) / real(ny);
                Ray r = cam.getRay(u, v);
                col += color(r, world, 0);
            }
            col /= real(ns);
            bitmap.setPel(i, j, int(255.99*sqrt(col[0])), int(255.99*sqrt(col[1])), int(255.99*sqrt(col[2])));
        }
    }
    std::ofstream ofile("1.bmp", std::ios::out | std::ios::binary);
    bitmap.write(ofile);
    ofile.close();

    delete world;
    for (int i = 0; i < 53; i++)
    {
        delete list[i];
    }

    return 0;
}