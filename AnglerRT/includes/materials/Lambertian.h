#pragma once

#include "Material.h"

class Lambertian : public Material{
    public:
        Lambertian(Color color) : albedo(color){};
        bool BSDF(const Ray&, Color&, Interaction&, Ray&) const override;

    private:
        Color albedo;
};