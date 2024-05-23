#pragma once
#include <pch.h>
#include <entt/entity/registry.hpp>

#include <GLMaterial.h>

namespace GLEngine
{

  using GLMaterial::Material;


  struct MeshRenderer
  {
    std::vector<GLuint> VBO;
    std::vector<Material> materials;

    MeshRenderer();
  };
}