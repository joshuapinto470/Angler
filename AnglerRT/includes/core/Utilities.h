#pragma once

#include "Geometry.h"
#include "spdlog/spdlog.h"

#include <cmath>
#include <limits>
#include <memory>

#define FLOAT_AS_DOUBLE

#ifdef FLOAT_AS_DOUBLE
#define Float double
#else
#define Float float
#endif

typedef Vec3<Float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<int> Vec3i;

typedef Vec3d Point;
typedef Vec3<float> Color;

typedef Vec2<Float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<int> Vec2i;
typedef Vec2<int> Position2D;
typedef Vec2<int> Point2;

typedef Mat44<float> Mat44f;
typedef Mat44<int> Mat44i;

// Constants
const double Infinity = std ::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;
const double PI_INV = 1 / PI;
const float INV_255 = 1 / 255.0;

// Helper functions

inline double degrees_to_radians(double degrees) {
    return degrees * 0.017453292519943295;
}

inline Float Clamp(Float x, Float min, Float max) {
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

template <typename T> T Lerp(float t, T start, T end) {
    return (1.0 - t) * start + t * end;
}

template <typename T> inline bool NearZero(const Vec3<T> &v) {
    return (v.x() < 1e-8) && (v.y() < 1e-8) && (v.z() < 1e-8);
}

inline Vec3f refract(const Vec3f &vector, const Vec3f &normal, double angleOfRefraction) {
    Float cos_theta = fmin(-vector.dot(normal), 1.0);
    Vec3f r_out_perp = angleOfRefraction * (-vector + cos_theta * normal);
    Vec3f r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.LengthSquared())) * normal;
    return r_out_perp + r_out_parallel;
}

template <typename T> inline Vec3<T> reflect(const Vec3<T> &v, const Vec3<T> &n) {
    return v - 2 * v.dot(n) * n;
}