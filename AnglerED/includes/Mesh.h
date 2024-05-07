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

class Shader {
   public:
    Shader();
    Shader(const char *, const char *);
    void use();
    void setInt(const std::string &, int) const;
    void setBool(const std::string &, bool) const;
    void setFloat(const std::string &, float) const;
    void setVec2(const std::string &, const glm::vec2 &) const;
    void setVec2(const std::string &, float, float) const;
    void setVec3(const std::string &, const glm::vec3 &) const;
    void setVec3(const std::string &, float, float, float) const;
    void setVec4(const std::string &, float, float, float, float) const;
    void setVec4(const std::string &, const glm::vec4 &) const;
    void setMat4(const std::string &, const glm::mat4 &) const;
    void setMat2(const std::string &, const glm::mat2 &) const;
    void setMat3(const std::string &, const glm::mat3 &) const;
    unsigned int ID;
};