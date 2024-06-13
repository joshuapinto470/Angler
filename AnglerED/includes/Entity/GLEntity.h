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
        std::vector<Material*> materials;

      public:
        MeshRenderer() = default;
        MeshRenderer(MeshFilter &);
        MeshRenderer(MeshFilter&, std::vector<Material*>&);

        const std::vector<Material*>& getMaterial();
        const std::vector<VertexBuffer>& getVbo();
    };
} // namespace GLEngine