//
// Created by Joshua on 21-06-2021.
//
#include "Camera.h"

Camera::Camera(double vFov, double aspect_ratio, Point lookFrom, Point lookAt, Vec3f vUp) {
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

Camera::Camera(){
    Vec3f w = (Point(0, 0, 0) - Point(0, 1, 0)).Normalize();
    Vec3f u = Point(0, 1, 0).cross(w).Normalize();
    Vec3f v = w.cross(u);

    origin = Point(0, 0, 0);

    Float AR = 16.0 / 9.0;
    Float theta = 90.0 * deg2rad;
    Float h = tan(theta / 2.0);

    Float VP_Height = 2.0 * h;
    Float VP_Width = AR * VP_Height;
    Float focalLength = 1.0;

    horizontal = VP_Width * u;
    vertical = VP_Height * v;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w;
}

Ray Camera ::get_ray(Float s, Float t) const {
    return { origin, (Vec3d)lowerLeftCorner + s * horizontal + t * vertical - origin };
}