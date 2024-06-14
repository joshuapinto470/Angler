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


struct Model
{
    MeshFilter m_mesh;
    std::vector<Model> m_children;

    Model() = default;
    Model(MeshFilter& m) {m_mesh = m;}
};