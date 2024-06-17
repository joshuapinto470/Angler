#pragma once
#include <pch.h>
#include <entt/entity/registry.hpp>

#include <GLMaterial.h>
#include <GLModel.h>
#include <GLEngine.h>

namespace GLEngine
{
    class MeshRenderer
    {
        std::vector<IndexedBuffer> vbos;
        std::vector<Material> materials;

      public:
        MeshRenderer() = default;
        MeshRenderer(MeshFilter &, MaterialList &);

        const std::vector<IndexedBuffer> &getVbo();
        const std::vector<Material> &getMaterials();
    };
} // namespace GLEngine