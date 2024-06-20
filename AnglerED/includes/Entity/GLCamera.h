#pragma once

#include <pch.h>
#include "GLEngine.h"

namespace GLEngine
{
    class Camera
    {
        glm::mat4 m_projection {};
        glm::mat4 m_view {};
      public:
        Camera() = default;
        explicit Camera(glm::mat4&);
        Camera(glm::mat4&, glm::mat4&);
        
        const glm::mat4& getProjection();
        const glm::mat4& getView();

        void setView(glm::mat4& view);
        void setProjection(glm::mat4& projection);
    };
} // namespace GLEngine
