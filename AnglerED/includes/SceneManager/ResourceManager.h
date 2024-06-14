#pragma once

#include <GLModel.h>
#include <GLMaterial.h>
#include <Shader.h>
#include <ModelLoader.h>

namespace ResourceManager
{
    typedef union {
        unsigned int repr;
        struct HandleData
        {
            unsigned char type;
            unsigned char flags;
            unsigned short int id;
        } data;
    } ResourceHandle;

    class Resource
    {
      private:
        ResourceHandle m_handle;

      public:
        const ResourceHandle getHandle()
        {
            return m_handle;
        }
        const bool getFlags(unsigned flags)
        {
            return m_handle.data.flags & flags;
        }
        const void setFlags(unsigned flags)
        {
            m_handle.data.flags |= flags;
        }
    };

    class ResourceManager
    {
      public:
        ResourceManager();
        unsigned LoadModel(std::string &);
        unsigned LoadShader(std::string &);

        GLMesh &getMesh(unsigned);
        Shader &getShader(unsigned);
        GLEngine::Material &getMaterial(unsigned);

      private:
        std::vector<GLMesh> m_meshes;
        std::vector<GLEngine::Material> m_materials;
        std::vector<GLEngine::Texture> m_textures;
        std::vector<Shader> m_shaders;
    };
} // namespace ResourceManager