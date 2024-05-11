#pragma once

#include <pch.h>

#include <GLEngine.h>
#include <Shader.h>

/*
renderer should take the scene information
vao, shader id, material info, lighting info, camera etc
*/

namespace GLRenderer
{
    class Renderer
    {
    public:
        void Draw();
        void PrepareShader();

    private:
        GLuint programID; // currently bound shader
        std::vector<GLEngine::VertexBuffer> m_meshObjects;
    };
} // namespace Renderer
