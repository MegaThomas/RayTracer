#include <iostream>
#include <fstream>
#include "typeDef.h"
#include "bmp.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable.h"
#include "hitableList.h"

Vec3 color(const Ray& r, Hitable *world)
{
    HitRecord tempRec;
    if (world->hit(r, 0.0, 1e10, tempRec))
    {
        return 0.5*Vec3(tempRec.normal.x() + 1, tempRec.normal.y() + 1, tempRec.normal.z() + 1);
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

    int nx = 200;
    int ny = 100;
    BMP bitmap(nx, ny);
    Vec3 vLowerLeft(-2.0, -1.0, -1.0);
    Vec3 vHor(4.0, 0.0, 0.0);
    Vec3 vVer(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);
    Hitable *list[2];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
    Hitable *world = new HitableList(list, 2);
    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; ++i)
        {
            real u = real(i) / real(nx);
            real v = real(j) / real(ny);
            Ray r(origin, vLowerLeft + u * vHor + v * vVer);

            Vec3 col = color(r, world);
            bitmap.setPel(i, j, int(255.99*col[0]), int(255.99*col[1]), int(255.99*col[2]));
        }
    }
    std::ofstream ofile("1.bmp", std::ios::out | std::ios::binary);
    bitmap.write(ofile);
    ofile.close();

    return 0;
}