#pragma once

#include <pch.h>
#include <DataStructures.h>

// The OpenGL render context

namespace GLEngine
{
    class VertexBuffer
    {
      private:
        GLuint VBO, VAO;
        unsigned size;

      public:
        VertexBuffer() : VBO(0), VAO(0), size(0)
        {
        }
        // ~VertexBuffer();
        int Init(const std::vector<DS::Vertex> &);
        void Render() const;
        void Destroy();
        void Bind() const;
        void Unbind() const;
    };

    class FrameBuffer
    {
      private:
        GLuint FBO;
        GLuint m_texture;
        GLuint RBO;

      public:
        FrameBuffer() = default;
        ~FrameBuffer();
        void Init(unsigned, unsigned);
        void Bind() const;
        void Unbind() const;
        GLuint getTexture() {return m_texture;};
    };

    class GLEngine
    {
      public:
        GLEngine() = default;
        void Init();
        void PreFrame();
        void PostFrame();
        void End();
    };
} // namespace GLEngine
