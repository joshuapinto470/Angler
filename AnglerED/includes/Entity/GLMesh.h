#pragma once

#include <pch.h>
#include <DataStructures.h>

struct MeshData
{
    std::vector<DS::Vertex> m_vertices;
    std::vector<unsigned> m_indices;
};

struct GLMesh
{
    std::string m_name;
    std::shared_ptr<MeshData> m_mesh;
};