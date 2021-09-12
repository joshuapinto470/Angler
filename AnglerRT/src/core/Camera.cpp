//
// Created by Joshua on 21-06-2021.
//
#include "Camera.h"

Camera::Camera(double vFov, double aspect_ratio, Point lookFrom, Point lookAt, Vec3f vUp)
{
    Vec3f w = (lookFrom - lookAt).Normalize();
    Vec3f u = vUp.cross(w).Normalize();
    Vec3f v = w.cross(u);

    origin = lookFrom;

    Float AR = aspect_ratio;
    Float theta = vFov * deg2rad;
    Float h = tan(theta / 2.0);

    Float VP_Height = 2.0 * h;
    Float VP_Width = AR * VP_Height;
    Float focalLength = 1.0;

    horizontal = VP_Width * u;
    vertical = VP_Height * v;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w;
}

Ray Camera :: get_ray(Float s, Float t) const 
{
    return {origin, (Vec3d)lowerLeftCorner + s * horizontal + t * vertical - origin};
}