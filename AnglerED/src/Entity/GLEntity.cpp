#include <GLEntity.h>

namespace GLEngine
{
    MeshRenderer::MeshRenderer(MeshFilter &mesh)
    {
        for (const auto &i : mesh.m_meshes)
        {
            IndexedBuffer v;
            v.Init(i.m_mesh.m_vertices, i.m_mesh.m_indices);
            vbos.push_back(v);
        }
    }
    MeshRenderer::MeshRenderer(MeshFilter &mesh, std::vector<Material *> &materials)
    {
        for (const auto &i : mesh.m_meshes)
        {
            IndexedBuffer v;
            v.Init(i.m_mesh.m_vertices, i.m_mesh.m_indices);
            vbos.push_back(v);
        }
        this->materials = materials;
    }

    const std::vector<Material *> &MeshRenderer::getMaterial()
    {
        return materials;
    }

    const std::vector<IndexedBuffer> &MeshRenderer::getVbo()
    {
        return vbos;
    }
} // namespace GLEngine