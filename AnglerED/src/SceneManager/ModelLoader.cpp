#include <ModelLoader.h>
#include "spdlog/spdlog.h"
#include <GLEngine.h>
#include <GLMaterial.h>

using GLEngine::Vertex;

#ifndef USE_ASSIMP
// Load TinyObjLoader if Assimp is not used.
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#endif

void printvec3(const std::string s, const tinyobj::real_t v[3])
{
    std::cout << s.c_str() << ": " << v[0] << ", " << v[1] << ", " << v[2] << "\n";
}

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
    // reader_config.mtl_search_path = "/home/joshua/Projects/Angler/res/";
    reader_config.triangulate = true;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, reader_config))
    {
        if (!reader.Error().empty())
        {
            spdlog::error("OBJ File Reader {}", reader.Error());
        }
        return Model();
    }

    if (!reader.Warning().empty())
    {
        spdlog::warn("OBJ Filer Reader {} ", reader.Warning());
    }

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();
    auto &materials = reader.GetMaterials();

    std::vector<Mesh> meshes;
    meshes.reserve(shapes.size());

    for (const auto &shape : shapes)
    {
        size_t index_offset = 0;
        std::vector<Vertex> vertices;
        std::vector<unsigned> indices;

        vertices.reserve(shape.mesh.num_face_vertices.size() * 3);

        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
            int fv = size_t(shape.mesh.num_face_vertices[f]); // This should be 3 since we triangulate the mesh.
            assert(fv == 3);
            Vertex vertex;
            // vertex.mat_id = 0;
            unsigned vi; // vertex index;

            int mat_id = shape.mesh.material_ids[f];
            if (mat_id >= 0)
            {
                tinyobj::material_t mat = materials[mat_id];
                vertex.Diffuse = glm::vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
                // vertex.mat_id = mat_id;
            }
        
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
                vertices.push_back(vertex);
            }

            indices.push_back(vi);
            index_offset += fv;
        }

        meshes.emplace_back(vertices, indices);
    }
    return Model(meshes);
}
#endif
