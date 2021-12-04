#pragma once

#include "Shape.h"

class Sphere : public Shape {
  private:
    Point mCenter;
    Float mRadius{};
    std ::shared_ptr<Material> material;

  public:
    Sphere() = default;
    Sphere(Point center, Float radius, std::shared_ptr<Material> mat)
        : mCenter(center), mRadius(radius), material(mat){};

    bool Hit(const Ray &, Float, Float, Interaction &) const override;
    bool Bound(Float time0, double time1, Bounds3 &output_box) const override;
};