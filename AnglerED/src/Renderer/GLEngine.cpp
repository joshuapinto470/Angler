#include <GLEngine.h>
#include <DataStructures.h>

using DS::Vertex;

namespace GLEngine
{
    void GLEngine::Init()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void GLEngine::PostFrame()
    {
    }

    void GLEngine::PreFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLEngine::End()
    {
    }

} // namespace GLEngine

namespace GLEngine
{
    GLuint generateTexture(unsigned char *data, int width, int height, int nrChannels)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        if (data)
        {
            GLenum format = GL_RGB;
            if (nrChannels == 1)
            {
                format = GL_RED;
            }
            else if (nrChannels == 3)
            {
                format = GL_RGB;
            }
            else if (nrChannels == 4)
            {
                format = GL_RGBA;
            }

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            spdlog::error("GLTexture Texture failed to load!");
        }

        return textureID;
    }

} // namespace GLEngine

// GL Vertex Object
namespace GLEngine
{
    int VertexBuffer::Init(const std::vector<Vertex> &vertices)
    {
        size = vertices.size();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normals));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return 0;
    }

    void VertexBuffer::Render() const
    {
        glDrawArrays(GL_TRIANGLES, 0, size);
        // glBindVertexArray(0);
    }

    void VertexBuffer::Destroy()
    {
    }

    void VertexBuffer::Bind() const
    {
        glBindVertexArray(VAO);
    }

    void VertexBuffer::Unbind()
    {
        glBindVertexArray(0);
    }
} // namespace GLEngine

// Index Buffer
namespace GLEngine
{
    void IndexedBuffer::Init(const std::vector<Vertex> &vertices, const std::vector<unsigned> &indices)
    {
        size = indices.size();
        glGenVertexArrays(1, &VAO);

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normals));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

        // glEnableVertexAttribArray(3);
        // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Tangent));

        // glEnableVertexAttribArray(4);
        // glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void
        // *)offsetof(Vertex, Bitangent));

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexedBuffer::Render() const
    {
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    }

    void IndexedBuffer::Destroy()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        VAO = 0;
        VBO = 0;
        EBO = 0;
    }

    void IndexedBuffer::Bind() const
    {
        glBindVertexArray(VAO);
    }

    void IndexedBuffer::Unbind() const
    {
        glBindVertexArray(0);
    }

} // namespace GLEngine

// Framebuffer
namespace GLEngine
{
    void FrameBuffer::Init(unsigned width, unsigned height)
    {
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
        {
            spdlog::error("GLEngine::FRAMEBUFFER {}", "Framebuffer generation failed!");
            // glDeleteFramebuffers(1, &FBO);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void FrameBuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    }

    void FrameBuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::Clear() const
    {
        Bind();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Unbind();
    }

    void FrameBuffer::RescaleBuffer(float width, float height) const
    {
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    }

    FrameBuffer::~FrameBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &FBO);
        glDeleteTextures(1, &m_texture);
        glDeleteRenderbuffers(1, &RBO);
    }
} // namespace GLEngine
