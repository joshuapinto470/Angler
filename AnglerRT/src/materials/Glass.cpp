//
// Created by Joshua on 17-06-2021.
//
#include "Glass.h"

bool Glass :: BSDF(const Ray& ray_in, Color& color, Interaction& interaction, Ray& ray_out) const{
    //Float p = random_double(0, 1);
    color = base_color;
    Float refraction_ratio = interaction.front_face ? (1.0 / IOR) : IOR;
    Vec3f unit_vector = ray_in.Direction().Normalize();

    Float cos_theta = fmin(-unit_vector.dot(interaction.Normal), 1.0);
    Float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3f  direction;
    if(cannot_refract)
        direction = reflect(unit_vector, interaction.Normal);
    else
        direction = refract(unit_vector, interaction.Normal, refraction_ratio);

    ray_out = Ray(interaction.hitLocation, direction);
    return true;
}