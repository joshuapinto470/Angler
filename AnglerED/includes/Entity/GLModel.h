#pragma once

#include <pch.h>
#include <DataStructures.h>
#include <GLMaterial.h>

struct MeshData
{
    std::vector<DS::Vertex> m_vertices;
    std::vector<unsigned> m_indices;
};

struct GLMesh
{
    std::string m_name;
    MeshData m_mesh;
    unsigned m_material;
};

struct MeshFilter
{
    std::vector<GLMesh> m_meshes;
};

struct meshNode
{
    std::vector<unsigned> m_meshIndices;
    glm::mat4 m_transformation;
};

typedef DS::Node<meshNode> MeshNode;

struct Model
{
    MeshFilter m_mesh;
    std::shared_ptr<MeshNode> m_root;
    GLEngine::MaterialDataList m_materials;
    GLEngine::TextureList m_textures;

    Model() = default;
};