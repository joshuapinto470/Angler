#pragma once

#include <pch.h>
#include <GLEngine.h>

// struct Vertex
// {
//     glm::vec3 Position;
//     glm::vec3 Normals;
//     glm::vec3 Diffuse;
//     glm::vec2 uv;
// };

struct MeshData
{
    std::vector<GLEngine::Vertex> m_vertices;
    std::vector<unsigned> m_indices;
};

class Mesh
{
private:
    MeshData* m_mesh;
    glm::mat4 m_transform;

    GLEngine::VertexBuffer vBuffer;
public:
    Mesh() = default;
    Mesh(std::vector<GLEngine::Vertex>, std::vector<unsigned>);
    void initMesh();
    void Draw() const;
    ~Mesh();
};