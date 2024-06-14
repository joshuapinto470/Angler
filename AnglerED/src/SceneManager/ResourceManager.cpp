#include <ResourceManager.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace ResourceManager
{
    ResourceManager::ResourceManager()
    {
        Shader defaultShader("/home/joshua/Projects/Angler/AnglerED/shaders/base.vert",
                             "/home/joshua/Projects/Angler/AnglerED/shaders/base.frag");
        m_shaders.push_back(defaultShader);
    }

    unsigned ResourceManager::LoadModel(std::string &path)
    {
        AssimpLoader loader;
        loader.LoadModel(path);
        std::vector<GLMesh> meshes = loader.getMesh();
        std::vector<GLEngine::MaterialData> materials = loader.getMaterials();
        std::vector<GLEngine::Texture> textures = loader.getTextures();

        for (unsigned i = 0; i < textures.size(); i++)
        {
            std::string path = textures[i].path;
            int width, height, nrComponents;
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
            textures[i].id = GLEngine::generateTexture(data, width, height, nrComponents);
            stbi_image_free(data);
        }

        return 0;
    }

    unsigned ResourceManager::LoadShader(std::string &path)
    {
        return 0;
    }

    GLMesh &ResourceManager::getMesh(unsigned i)
    {
        return m_meshes[i];
    }

    Shader &ResourceManager::getShader(unsigned i)
    {
        return m_shaders[i];
    }

    GLEngine::Material &ResourceManager::getMaterial(unsigned i)
    {
        return m_materials[i];
    }

} // namespace ResourceManager