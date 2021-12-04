#pragma once

#include "Ray.h"
#include "Utilities.h"

class Camera {
  public:
    Camera(Float vFov, Float aspect_ratio, Point lookFrom, Point lookAt, Vec3f vUp);

    Ray get_ray(Float, Float) const;

  private:
    Point origin;
    Point lowerLeftCorner;
    Vec3f horizontal;
    Vec3f vertical;
};