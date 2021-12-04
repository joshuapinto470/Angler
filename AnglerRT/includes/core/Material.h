#pragma once

#include "Random.h"
#include "Ray.h"
#include "Shape.h"
#include "Utilities.h"

class Material {
  public:
    virtual bool BSDF(const Ray &, Color &, Interaction &, Ray &) const = 0;
};