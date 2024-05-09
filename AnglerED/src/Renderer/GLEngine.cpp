#include <GLEngine.h>

namespace GLEngine
{
    void GLEngine::Init()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glClearColor(0.8f, 0.1f, 0.2f, 1.0f);
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
}

// GL Vertex Object
namespace GLEngine
{
    int VertexBuffer::Init(std::vector<Vertex> &vertices)
    {
        size = vertices.size();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *)offsetof(Vertex, Normals));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *)offsetof(Vertex, Diffuse));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *)offsetof(Vertex, uv));

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

    void VertexBuffer::Unbind() const
    {
        glBindVertexArray(0);
    }
} // namespace GLEngine
