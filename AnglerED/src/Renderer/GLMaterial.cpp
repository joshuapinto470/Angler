#include <GLMaterial.h>

namespace GLMaterial
{

    Material::Material()
    {
        diffuse = glm::vec3(1.0f, 0.2f, 0.0f);
        specular = glm::vec3(0.0f, 0.0f, 0.0f);
        roughness = 0.0f;
    }

    Material::Material(glm::vec3 diffuse, glm::vec3 spec, float, Shader * shader)
    {
        this->diffuse = diffuse;
        this->specular = spec;
        this->shader = shader;
    }

} // namespace GLMaterial
