#include <Mesh.h>
#include <iostream>

Mesh::Mesh(std::vector<GLEngine::Vertex> vertices, std::vector<unsigned> indices)
{
    m_vertices = vertices;
    m_indices = indices;
}

void Mesh::Draw() const
{
    vBuffer.Bind();
    vBuffer.Render();
    vBuffer.Unbind();
}

void Mesh::initMesh()
{
    vBuffer.Init(m_vertices);
}