//
// Created by Joshua on 23-06-2021.
//

#include "EnvironmentMap.h"

Color EnvironmentTexture ::MapTexture(Float x, Float y, Float z) const {
    // u-v map the 3-d points into the 2d image texture;
    Float u = 0.5 + (atan2(z, x) * 0.5 * PI_INV);
    Float v = 0.5 - asin(y) * PI_INV;

    u *= getWidth();
    v *= getHeight();

    return GetPixel(v, u);
}

Color EnvironmentTexture ::MapTexture(const Ray &ray) const {
    Vec3f dir = ray.Direction().Normalize();
    return MapTexture(dir.x(), dir.y(), dir.z());
}