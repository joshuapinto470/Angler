#include <GLEntity.h>

namespace GLEngine
{
    MeshRenderer::MeshRenderer(MeshFilter &mesh)
    {
        for (const auto &i : mesh.m_meshes)
        {
            VertexBuffer v;
            v.Init(i.m_mesh->m_vertices);
            vbos.push_back(v);
        }
    }

    void MeshRenderer::Render()
    {
        for (const auto &i : vbos)
        {
            i.Bind();
            i.Render();
            i.Unbind();
        }
    }
} // namespace GLEngine