#pragma once

#include <GLMesh.h>
#include <GLMaterial.h>

struct MeshFilter
{
    std::vector<GLMesh> m_meshes;
};

class Model
{
    MeshFilter m_mesh;
    std::vector<GLMaterial::Material*> m_material;

    public:
        Model() = default;
        Model(MeshFilter);
        Model(MeshFilter, std::vector<GLMaterial::Material*>);

        MeshFilter getMesh();
        std::vector<GLMaterial::Material*> getMaterial();
};