#pragma once

#include "Material.h"

class Dielectric : public Material {
    Float IOR{};
    static double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

  public:
    Dielectric() = default;
    explicit Dielectric(Float ior);
    bool BSDF(const Ray &, Color &, Interaction &, Ray &) const override;
};