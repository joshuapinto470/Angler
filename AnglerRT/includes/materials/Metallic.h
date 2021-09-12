#pragma once

#include "Material.h"

class Metallic : public Material{
    public:
        Metallic(const Color& color, Float rough) : albedo(color), Roughness(rough){};
        bool BSDF(const Ray&, Color&, Interaction&, Ray&) const override;

    private:
        Color albedo;
        Float Roughness;
};