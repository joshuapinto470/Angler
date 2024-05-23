#pragma once

#include <pch.h>
#include <GLEngine.h>

struct MeshData
{
    std::vector<DS::Vertex> m_vertices;
    std::vector<unsigned> m_indices;
};

class Mesh
{
private:
    std::shared_ptr<MeshData> m_mesh;
    GLEngine::VertexBuffer vBuffer;
public:
    Mesh() = default;
    Mesh(std::vector<DS::Vertex>, std::vector<unsigned>);
    void initMesh();
    void Draw() const;
    ~Mesh();
};

struct GLMesh
{
    std::string m_name;
    std::shared_ptr<MeshData> m_mesh;
};