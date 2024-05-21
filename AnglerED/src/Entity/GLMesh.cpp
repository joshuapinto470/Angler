#include <GLMesh.h>

Mesh::Mesh(std::vector<GLEngine::Vertex> vertices, std::vector<unsigned> indices)
{
    m_mesh = std::make_shared<MeshData>();
    m_mesh->m_vertices = vertices;
    m_mesh->m_indices = indices;

    m_transform = glm::mat4(1.0f);
}

void Mesh::Draw() const
{
    vBuffer.Bind();
    vBuffer.Render();
    vBuffer.Unbind();
}

void Mesh::initMesh()
{
    vBuffer.Init(m_mesh->m_vertices);
}

Mesh::~Mesh()
{
}
