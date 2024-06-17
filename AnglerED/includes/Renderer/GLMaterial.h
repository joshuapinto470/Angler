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
        std::string shaderName;
    };

    typedef std::vector<MaterialData> MaterialDataList;
    typedef std::vector<Material> MaterialList;
    typedef std::vector<Texture> TextureList;

} // namespace GLEngine
