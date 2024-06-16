#pragma once

#include <GLModel.h>
#include <pch.h>
#include <string>
#include <GLEngine.h>
#include <GLMaterial.h>
#include <DataStructures.h>

class ModelLoader
{
  public:
    ModelLoader() = default;
    virtual Model LoadModel(std::string) = 0;
};

#ifdef USE_ASSIMP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class AssimpLoader : public ModelLoader
{
  private:
    std::vector<GLMesh> m_meshes;
    std::vector<GLEngine::MaterialData> m_materials;
    std::vector<GLEngine::Texture> m_textures;
    std::string m_directory;

    MeshData loadMesh(aiMesh *);
    GLEngine::MaterialData loadMaterial(aiMaterial *);

  public:
    Model LoadModel(std::string) override;

    std::vector<GLMesh> getMesh()
    {
        return m_meshes;
    }
    std::vector<GLEngine::MaterialData> getMaterials()
    {
        return m_materials;
    }
    std::vector<GLEngine::Texture> getTextures()
    {
        return m_textures;
    }
};
#endif

#ifndef USE_ASSIMP
class ObjLoader : public ModelLoader
{
  public:
    Model LoadModel(std::string);
};
#endif