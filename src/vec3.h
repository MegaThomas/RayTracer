#ifndef __VEC3_H__
#define __VEC3_H__

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "typeDef.h"

class Vec3
{
public:
    Vec3() {};
    Vec3(real a)
    {
        e[0] = a;
        e[1] = a;
        e[2] = a;
    }
    Vec3(real e0, real e1, real e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    };
    ~Vec3() {};

    void set(real e0, real e1, real e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    };

    inline real x() const { return e[0]; }
    inline real y() const { return e[1]; }
    inline real z() const { return e[2]; }
    inline real r() const { return e[0]; }
    inline real g() const { return e[1]; }
    inline real b() const { return e[2]; }

    inline real operator[](int i) const { return e[i]; }
    inline real dot(const Vec3 &v) const
    {
        return v[0] * e[0] + v[1] * e[1] + v[2] * e[2];
    }
    inline Vec3 cross(const Vec3 &v)
    {
        return Vec3(
            e[1] * v[2] - v[1] * e[2],
            e[2] * v[0] - v[2] * e[0],
            e[0] * v[1] - v[0] * e[1]
        );
    }


    inline Vec3& operator+=(const Vec3 &v)
    {
        e[0] += v[0];
        e[1] += v[1];
        e[2] += v[2];
        return *this;
    }
    inline Vec3& operator-=(const Vec3 &v)
    {
        e[0] -= v[0];
        e[1] -= v[1];
        e[2] -= v[2];
        return *this;
    }
    inline Vec3& operator*=(const Vec3 &v)
    {
        e[0] *= v[0];
        e[1] *= v[1];
        e[2] *= v[2];
        return *this;
    }
    inline Vec3& operator/=(const Vec3 &v)
    {
        e[0] /= v[0];
        e[1] /= v[1];
        e[2] /= v[2];
        return *this;
    }
    inline Vec3& operator*=(const real t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    inline Vec3& operator/=(const real t)
    {
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    }
    inline real norm2() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    inline real squared_norm2() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline Vec3& normalize()
    {
        real l = this->norm2();
        e[0] /= l;
        e[1] /= l;
        e[2] /= l;
        return *this;
    }

private:
    real e[3];
};

//! v+v

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

//! a+v

inline Vec3 operator+(real a, const Vec3 &v2)
{
    return Vec3(a + v2[0], a + v2[1], a + v2[2]);
}

inline Vec3 operator-(real a, const Vec3 &v2)
{
    return Vec3(a - v2[0], a - v2[1], a - v2[2]);
}

inline Vec3 operator*(real a, const Vec3 &v2)
{
    return Vec3(a * v2[0], a * v2[1], a * v2[2]);
}

inline Vec3 operator/(real a, const Vec3 &v2)
{
    return Vec3(a / v2[0], a / v2[1], a / v2[2]);
}

//! v+a

inline Vec3 operator+(const Vec3 &v1, real a)
{
    return Vec3(v1[0] + a, v1[1] + a, v1[2] + a);
}

inline Vec3 operator-(const Vec3 &v1, real a)
{
    return Vec3(v1[0] - a, v1[1] - a, v1[2] - a);
}

inline Vec3 operator*(const Vec3 &v1, real a)
{
    return Vec3(v1[0] * a, v1[1] * a, v1[2] * a);
}

inline Vec3 operator/(const Vec3 &v1, real a)
{
    return Vec3(v1[0] / a, v1[1] / a, v1[2] / a);
}

#endif // !__VEC3_H__
