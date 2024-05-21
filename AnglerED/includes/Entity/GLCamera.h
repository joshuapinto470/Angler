#pragma once

#include <pch.h>

namespace GLEngine
{
    class Camera
    {
        glm::mat4 m_projection;
        glm::mat4 m_view;
      public:
        Camera() = default;
        Camera(glm::mat4);
        Camera(glm::mat4, glm::mat4);
        
        const glm::mat4& getProjection();
        const glm::mat4& getView();
         
    };
} // namespace GLEngine
