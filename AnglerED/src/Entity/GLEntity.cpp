#include <GLEntity.h>

namespace GLEngine
{
    MeshRenderer::MeshRenderer(MeshFilter &mesh, MaterialList &materialPool)
    {
        for (const auto &i : mesh.m_meshes)
        {
            IndexedBuffer v;
            v.Init(i.m_mesh.m_vertices, i.m_mesh.m_indices);
            vbos.push_back(v);
            materials.push_back(materialPool[i.m_material]);
        }
    }

    const std::vector<IndexedBuffer> &MeshRenderer::getVbo()
    {
        return vbos;
    }
    const std::vector<Material> &MeshRenderer::getMaterials()
    {
        return materials;
    }
} // namespace GLEngine