#pragma once

#include "Utilities.h"
#include "Ray.h"
#include "Shape.h"
#include "Random.h"

class Material{
    public:
        virtual bool BSDF(const Ray&, Color&, Interaction&, Ray&) const = 0;
};