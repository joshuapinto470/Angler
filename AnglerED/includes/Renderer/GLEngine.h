#pragma once

#include <pch.h>

// The OpenGL render context

namespace GLEngine
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normals;
        glm::vec3 Diffuse;
        glm::vec2 uv;
    };

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
        int Init(const std::vector<Vertex> &);
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
