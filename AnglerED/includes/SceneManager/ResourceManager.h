#pragma once

#include <GLMesh.h>
#include <GLMaterial.h>
#include <Shader.h>

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
        ResourceManager() = default;
        unsigned LoadMesh(GLMesh &);
        unsigned LoadShader(Shader &);
        unsigned LoadMaterial(GLMaterial::Material &);

        GLMesh &getMesh(unsigned);
        Shader &getShader(unsigned);
        GLMaterial::Material &getMaterial(unsigned);

      private:
        std::vector<GLMesh> m_meshes;
        std::vector<GLMaterial::Material> m_materials;
        std::vector<Shader> m_shaders;
    };
} // namespace ResourceManager