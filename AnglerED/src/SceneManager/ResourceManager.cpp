#include <ResourceManager.h>

namespace ResourceManager
{
    unsigned ResourceManager::LoadMesh(GLMesh &mesh)
    {
        m_meshes.push_back(mesh);
        return m_meshes.size();
    }

    unsigned ResourceManager::LoadShader(Shader &shader)
    {
        m_shaders.push_back(shader);
        return m_shaders.size();
    }

    unsigned ResourceManager::LoadMaterial(GLMaterial::Material &material)
    {
        m_materials.push_back(material);
        return m_materials.size();
    }

    GLMesh &ResourceManager::getMesh(unsigned i)
    {
        return m_meshes[i];
    }

    Shader &ResourceManager::getShader(unsigned i)
    {
        return m_shaders[i];
    }

    GLMaterial::Material &ResourceManager::getMaterial(unsigned i)
    {
        return m_materials[i];
    }

} // namespace ResourceManager