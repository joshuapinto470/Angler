#pragma once
#include <pch.h>
#include <Shader.h>

namespace GLEngine
{
    class Light
    {
      protected:
        glm::vec3 m_position;
        glm::vec3 m_color;

      public:
        virtual void SetShader(Shader &) = 0;
    };

    class PointLight : public Light
    {
        float m_power;

      public:
        PointLight() = default;
        PointLight(glm::vec3 &, glm::vec3 &);
        PointLight(glm::vec3 &, glm::vec3 &, float);

        void SetShader(Shader &) override;
    };
} // namespace GLEngine
