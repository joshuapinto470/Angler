#include "Dielectric.h"


Dielectric::Dielectric(Float ior):
IOR(ior)
{
}

bool Dielectric::BSDF(const Ray &ray_in, Color &attenuation , Interaction &interaction, Ray &ray_out) const {
    
    attenuation = Color(1.0, 1.0, 1.0);
    Float refraction_ratio = interaction.front_face ? (1.0 / IOR) : IOR;

    Vec3f unit_direction = ray_in.Direction().Normalize();

    Float cos_theta = fmin(unit_direction.dot(-interaction.Normal), 1.0);
    Float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3f direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, interaction.Normal);
    else
        direction = refract(unit_direction, interaction.Normal, refraction_ratio);

    ray_out = Ray(interaction.hitLocation, direction);
    return true;
}
