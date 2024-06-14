#pragma once
#include <pch.h>
#include <Shader.h>

namespace GLEngine
{
    struct Texture
    {
        GLuint id;
        std::string type;
        std::string path;
    };

    struct MaterialData
    {
        std::string name;
        glm::vec3 diffuse;
        std::vector<Texture> m_textures;
    };

    struct Material
    {
        MaterialData data;
        unsigned shaderIndex;
    };
} // namespace GLMaterial
