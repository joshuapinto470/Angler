#include <ModelLoader.h>
#include "spdlog/spdlog.h"

#ifndef USE_ASSIMP
// Load TinyObjLoader if Assimp is not used.
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#endif

ModelLoader ::ModelLoader()
{
}

ModelLoader ::~ModelLoader()
{
}

#ifdef USE_ASSIMP
Model ModelLoader ::LoadModel(std ::string path)
{
}
#else
Model ModelLoader ::LoadModel(std ::string path)
{
    tinyobj::ObjReaderConfig reader_config;
    // .mtl search path same as model directory
    reader_config.mtl_search_path = "/home/joshua/Projects/Angler/res/";
    // reader_config.triangulate = true;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, reader_config))
    {
        if (!reader.Error().empty())
        {
            spdlog::error("OBJ File Reader {}", reader.Error());
        }
    }

    if (!reader.Warning().empty())
    {
        spdlog::warn("OBJ Filer Reader {} ", reader.Warning());
    }

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();
    auto &materials = reader.GetMaterials();

    std::vector<Mesh> meshes;

    for (const auto &shape : shapes)
    {
        size_t index_offset = 0;
        std::vector<Vertex> vertices;
        std::vector<unsigned> indices;

        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
            int fv = 3; // This should be 3 since we triangulate the mesh.
            Vertex vertex;
            unsigned vi; // vertex index;

            for (size_t v = 0; v < fv; v++)
            {
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                vi = idx.vertex_index;

                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                vertex.Position = glm::vec3(vx, vy, vz);

                if (idx.normal_index >= 0)
                {
                    tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                    vertex.Normals = glm::vec3(nx, ny, nz);
                }

                if (idx.texcoord_index >= 0)
                {
                    tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    vertex.uv = glm::vec2(tx, ty);
                }
            }

            vertices.push_back(vertex);
            indices.push_back(vi);
            index_offset += fv;
        }

        meshes.push_back(Mesh(vertices, indices));
    }
    return Model(meshes);
}
#endif