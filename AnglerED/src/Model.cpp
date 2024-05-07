#include <Model.h>


Model :: Model(std::vector<Mesh> mesh)
{
    m_mesh = mesh;
}

void Model :: PrintModelInfo()
{
    for(const auto& mesh : m_mesh)
    {
        mesh.PrintMeshInfo();
    }
}