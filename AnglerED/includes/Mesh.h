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


class Mesh
{
private:
    std::vector<GLEngine::Vertex> m_vertices;
    std::vector<unsigned> m_indices;
    // GLuint VBO, EBO, VAO;
    GLEngine::VertexBuffer vBuffer;
public:
    Mesh() = default;
    Mesh(std::vector<GLEngine::Vertex>, std::vector<unsigned>);
    void initMesh();
    void Draw() const;
    ~Mesh() {}
};