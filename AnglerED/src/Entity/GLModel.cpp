#include <GLModel.h>

Model::Model(std::vector<Mesh> mesh)
{
    m_mesh = mesh;
}

void Model::Draw()
{
    for (const auto &mesh : m_mesh)
    {
        mesh.Draw();
    }
}

void Model::initModel()
{
    for (int i = 0; i < m_mesh.size(); i++)
    {
        m_mesh[i].initMesh();
    }
}