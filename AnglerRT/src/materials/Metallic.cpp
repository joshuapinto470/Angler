#include "Metallic.h"

bool Metallic ::BSDF(const Ray &ray_in, Color &color, Interaction &interaction, Ray &ray_out) const {
    Vec3f reflected = reflect(ray_in.Direction().Normalize(), interaction.Normal);
    ray_out = Ray(interaction.hitLocation, reflected + Roughness * random_in_unit_sphere());
    color = albedo;
    return ray_out.Direction().dot(interaction.Normal) > 0;
}