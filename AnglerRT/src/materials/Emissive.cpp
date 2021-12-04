#include "Emissive.h"

bool Emissive ::BSDF(const Ray &ray_in, Color &color, Interaction &interaction, Ray &ray_out) const {
    color = base_color * strength;
    return false; // Dont bounce anymore rays.
}