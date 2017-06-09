#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ray.h"

class Camera
{
public:
    Camera()
    {
        vLowerLeft = Vec3(-2.0, -1.0, -1.0);
        vHor = Vec3(4.0, 0.0, 0.0);
        vVer = Vec3(0.0, 2.0, 0.0);
        vOrigin = Vec3(0.0, 0.0, 0.0);
    }
    ~Camera() {}

    Ray getRay(real u, real v)
    {
        return Ray(vOrigin, vLowerLeft + u * vHor + v * vVer);
    }

private:
    Vec3 vLowerLeft;
    Vec3 vHor;
    Vec3 vVer;
    Vec3 vOrigin;
};

#endif // !__CAMERA_H__
