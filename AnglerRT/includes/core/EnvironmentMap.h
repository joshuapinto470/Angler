//
// Created by Joshua on 18-06-2021.
//

#pragma once

#include "Ray.h"
#include "Texture.h"

class EnvironmentTexture : public Texture {
  public:
    EnvironmentTexture() = default;
    explicit EnvironmentTexture(const char *fileName) : Texture(fileName){};

    Color MapTexture(Float x, Float y, Float z) const;
    Color MapTexture(const Ray &) const;
};