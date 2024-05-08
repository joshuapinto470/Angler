#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <glad/glad.h>

#include <iostream>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normals;
    glm::vec3 Diffuse;
    glm::vec2 uv;
};


class Mesh
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned> m_indices;
    GLuint VBO, EBO, VAO;
public:
    Mesh() = default;
    Mesh(std::vector<Vertex>, std::vector<unsigned>);
    void PrintMeshInfo() const;
    void initMesh();
    void Draw() const;
    ~Mesh() {}
};