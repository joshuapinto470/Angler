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
    GLMaterial::Material m_material;

    public:
        Model() = default;
        Model(MeshFilter);
        Model(MeshFilter, GLMaterial::Material);

        MeshFilter getMesh();
        GLMaterial::Material getMaterial();
};