#include "Plane.h"

bool Plane::Hit(const Ray &ray, Float t_min, Float t_max, Interaction &inter) const {
    if (X.Hit(ray, t_min, t_max, inter)) {
        inter.material = material;
        return true;
    }

    if (Y.Hit(ray, t_min, t_max, inter)) {
        inter.material = material;
        return true;
    }

    return false;
}
bool Plane::Bound(Float time0, double time1, Bounds3 &output_box) const {
    return true;
}