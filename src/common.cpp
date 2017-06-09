#include "common.h"

Vec3 randomInUnitSphere()
{
    real theta = real(std::rand()) * 2.0 * Pi / RAND_MAX;
    real phi = real(std::rand()) * Pi / RAND_MAX - Pi_2;
    return Vec3(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi));
}

Vec3 reflect(const Vec3& v, const Vec3& N)
{
    return v - 2 * N * v.dot(N);
}
