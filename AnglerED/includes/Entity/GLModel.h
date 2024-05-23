#pragma once

#include <GLMesh.h>
#include <GLMaterial.h>

/* 144 bytes */
class Model
{
private:
    std::vector<Mesh> m_mesh;

public:
    Model() = default;
    Model(std::vector<Mesh>);
    void Draw();
    void initModel();
    ~Model() {}
};

struct MeshFilter
{
    std::vector<GLMesh> m_meshes;
};
