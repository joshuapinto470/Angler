#include <GLLight.h>

namespace GLEngine
{
    PointLight::PointLight(glm::vec3& position, glm::vec3& color)
    {
        m_color = color;
        m_position = position;
        m_power = 10.0f;
    }

    PointLight::PointLight(glm::vec3& position, glm::vec3& color, float power)
    {
        m_color = color;
        m_position = position;
        m_power = power;
    }

    void PointLight::SetShader(Shader& shader)
    {
        shader.setFloat("lightPower", m_power);
        shader.setVec3("lightPos", m_position);
        shader.setVec3("lightColor", m_color);
    }
} // namespace GLEngine
