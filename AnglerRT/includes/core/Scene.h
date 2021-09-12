#pragma once

#include "Utilities.h"
#include "Shape.h"
#include "EnvironmentMap.h"

#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"

#include <memory>
#include <utility>
#include <vector>

class Scene : public Shape{
    public:
        Scene();

        bool Hit(const Ray&, Float, Float, Interaction&) const override;
        void Add(const std::shared_ptr<Shape>& object) {objects.push_back(object);};

        void SetEnvironmentTexture(const std::shared_ptr<EnvironmentTexture>&);
        Color GetEnvironmentTexture(const Ray& ray) const;

    private:
        std::vector<std::shared_ptr<Shape>> objects;
        std::shared_ptr<EnvironmentTexture> mTexture;
};


