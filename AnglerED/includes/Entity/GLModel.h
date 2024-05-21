#pragma once

#include <GLMesh.h>
#include <GLMaterial.h>

/* 144 bytes */
class Model
{
private:
    std::vector<Mesh> m_mesh;
    glm::mat4 m_transform;
    std::vector<GLMaterial::DiffuseMaterial> m_material;
    std::string m_name;

public:
    Model();
    Model(std::vector<Mesh>);
    void Draw();
    void initModel();
    ~Model() {}
};
