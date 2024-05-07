#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include <iostream>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normals;
    glm::vec2 uv;
    /* data */
};


class Mesh
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned> m_indices;
public:
    Mesh() = default;
    Mesh(std::vector<Vertex>, std::vector<unsigned>);
    void PrintMeshInfo() const;
    ~Mesh() {}
};