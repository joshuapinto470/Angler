//
// Created by Joshua on 23-06-2021.
//
#include "Scene.h"


bool Scene :: Hit(const Ray& ray, Float t_min, Float t_max, Interaction& inter) const{
    Interaction tInter;
    bool HitAnything = false;
    Float ClosestObject = t_max;

    for (const auto& object : objects){
        if(object->Hit(ray, t_min, ClosestObject, tInter)){
            HitAnything = true;
            ClosestObject = tInter.t;
            inter = tInter;
        }
    }
    return HitAnything;
}

void Scene::SetEnvironmentTexture(const std::shared_ptr<EnvironmentTexture>& texture) {
    mTexture = texture;
}

Color Scene::GetEnvironmentTexture(const Ray& ray) const {
    if(mTexture)
        return mTexture->MapTexture(ray);
    return {0.02, 0.02, 0.075};
}

Scene::Scene() {
    mTexture = nullptr;
}

