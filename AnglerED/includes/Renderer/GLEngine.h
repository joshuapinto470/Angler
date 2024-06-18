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
        static void Unbind() ;
    };

    class IndexedBuffer
    {
      private:
        GLuint VBO, VAO, EBO;
        unsigned size;

      public:
        IndexedBuffer() : VBO(0), VAO(0), EBO(0){};
        int Init(const std::vector<DS::Vertex> &, const std::vector<unsigned> &);

        void Render() const;
        void Destroy();
        void Bind() const;
        static void Unbind() ;
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
        static void Unbind() ;
        void Clear() const;
        void RescaleBuffer(float, float) const;
        GLuint getTexture()
        {
            return m_texture;
        };
    };

    class GLEngine
    {
      public:
        GLEngine() = default;
        static void Init();
        static void PreFrame();
        void PostFrame();
        void End();
    };

    GLuint generateTexture(unsigned char*, int, int, int);
} // namespace GLEngine
