#pragma once

#include "Utilities.h"

class Ray{
    private:
        Vec3d direction;
        Point origin;
    public:
        Ray() : origin(0, 0, 0), direction(0, 0, 0) {};
        Ray(Point p, Vec3d d) : origin(p), direction(d) {};

        inline Point Origin() const {return origin;};
        inline Vec3d Direction() const {return direction;};
        
        Point at(Float t) const {
            return (Vec3d) origin + (t * direction);
        }
};