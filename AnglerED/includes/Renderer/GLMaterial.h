#pragma once
#include <pch.h>
#include <Shader.h>

namespace GLMaterial
{
    class DiffuseMaterial
    {
    private:

        glm::vec3 diffuse;

    public:
        void use(Shader& shader);
        void updateCamera();
        void updateLighting();
    };

} // namespace GLMaterial
