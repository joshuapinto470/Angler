#pragma once

#include "Material.h"

class Emissive : public Material{
    private:
        Color base_color;
        Float strength{0};
    public:
        Emissive() = default;
        Emissive(Color color, Float Strength) : base_color(color), strength(Strength) {};
        bool BSDF(const Ray&, Color&, Interaction&, Ray&) const override;
};