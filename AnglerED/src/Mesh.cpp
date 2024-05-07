#include <Mesh.h>
#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices)
{
    m_vertices = vertices;
    m_indices = indices;
}

void Mesh::PrintMeshInfo() const
{
    std::cout << "----MESH-----\n";
    std::cout << "Mesh size: " << m_vertices.size() << "\n";
    std::cout << "Index size: " << m_indices.size() << "\n";
    for (const auto &vertex : m_vertices)
    {
        std ::cout << "vert : " << vertex.Position.x << ", " << vertex.Position.y << ", " << vertex.Position.z << "\n";
        std ::cout << "norm : " << vertex.Normals.x << ", " << vertex.Normals.y << ", " << vertex.Normals.z << "\n";
        std ::cout << "uv : " << vertex.uv.x << ", " << vertex.uv.y << "\n---\n";
    }
    std::cout << "----END MESH----\n";
}