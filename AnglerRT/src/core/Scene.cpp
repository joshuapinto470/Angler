//
// Created by Joshua on 23-06-2021.
//
#include "Scene.h"

bool Scene ::Hit(const Ray &ray, Float t_min, Float t_max, Interaction &inter) const {
    Interaction tInter;
    bool HitAnything = false;
    Float ClosestObject = t_max;

    for (const auto &object : objects) {
        if (object->Hit(ray, t_min, ClosestObject, tInter)) {
            HitAnything = true;
            ClosestObject = tInter.t;
            inter = tInter;
        }
    }
    return HitAnything;
}

bool Scene::Bound(Float time0, double time1, Bounds3 &output_box) const {
    if (objects.empty())
        return false;

    Bounds3 temp_box;
    bool first_box = true;

    for (const auto &object : objects) {
        if (!object->Bound(time0, time1, temp_box))
            return false;
        output_box = first_box ? temp_box : Union(output_box, temp_box);
        first_box = false;
    }

    return true;
}

void Scene::SetEnvironmentTexture(const std::shared_ptr<EnvironmentTexture> &texture) {
    mTexture = texture;
}

Color Scene::GetEnvironmentTexture(const Ray &ray) const {
    if (mTexture)
        return mTexture->MapTexture(ray);

    Vec3f unit_direction = ray.Direction().Normalize();
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

size_t Scene::GetObjectsSize() const {
    return objects.size();
}

std::vector<std::shared_ptr<Shape>> Scene::GetObjects() const {
    return objects;
}

Scene::Scene() {
    mTexture = nullptr;
}

Bounds3 Union(Bounds3 box0, Bounds3 box1) {
    Vec3d small(fmin(box0.min().x(), box1.min().x()), fmin(box0.min().y(), box1.min().y()),
                fmin(box0.min().z(), box1.min().z()));

    Vec3d big(fmax(box0.max().x(), box1.max().x()), fmax(box0.max().y(), box1.max().y()),
              fmax(box0.max().z(), box1.max().z()));

    return Bounds3(small, big);
}
