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

void Mesh::Draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glBindVertexArray(0);
}

void Mesh::initMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, Normals));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, Diffuse));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, uv));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}