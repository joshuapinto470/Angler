#include "Lambertian.h"

bool Lambertian :: BSDF(const Ray& ray_in, Color& color, Interaction& interaction, Ray& ray_out) const{
    Vec3f target = interaction.Normal + random_unit_vector();
    
    if(NearZero(target))
        target = interaction.Normal;

    ray_out = Ray(interaction.hitLocation, target);
    color = albedo;
    return true;
}