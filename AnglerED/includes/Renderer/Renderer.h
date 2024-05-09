#pragma once

#include <pch.h>

#include <GLEngine.h>
#include <Shader.h>

namespace Renderer
{
    class Renderer
    {
    public:
        void Draw();

    private:
        std::vector<Shader> m_shaders;
        std::vector<GLEngine::VertexBuffer> m_MeshObjects;
    };
} // namespace Renderer
