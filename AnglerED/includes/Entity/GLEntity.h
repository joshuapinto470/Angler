#pragma once
#include <pch.h>
#include <entt/entity/registry.hpp>

#include <GLMaterial.h>
#include <GLModel.h>
#include <GLEngine.h>

namespace GLEngine
{

    using GLMaterial::Material;

    class MeshRenderer
    {
        std::vector<VertexBuffer> vbos;
        std::vector<Material> materials;

      public:
        MeshRenderer() = default;
        MeshRenderer(MeshFilter &);

        void Render();
    };
} // namespace GLEngine