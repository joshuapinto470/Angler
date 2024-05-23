#pragma once
#include <pch.h>
#include <Shader.h>

namespace GLMaterial
{
    struct Material
    {
        glm::vec3 diffuse;
        glm::vec3 specular;
        float roughness;

        Shader *shader;

        std::string name;

        Material();
        Material(glm::vec3, glm::vec3, float, Shader *);
    };
} // namespace GLMaterial
