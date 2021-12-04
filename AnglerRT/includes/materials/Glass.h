//
// Created by Joshua on 17-06-2021.
//
#pragma once

#include "Material.h"

class Glass : public Material {
  private:
    Color base_color;
    Float transparency{};
    Float IOR{};

  public:
    Glass() = default;
    Glass(Color color, Float Transparency, Float IndexOfRefraction)
        : base_color(color), transparency(Transparency), IOR(IndexOfRefraction){};

    bool BSDF(const Ray &, Color &, Interaction &, Ray &) const override;
};
