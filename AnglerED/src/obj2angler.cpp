/*
#define TINYOBJLOADER_IMPLEMENTATION

#include "obj2angler.h"

std::vector<std::vector<std::shared_ptr<Shape>>> LoadMeshFromFile(){

    std::string inputfile = "untitled.obj";
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config)) {
    if (!reader.Error().empty()) {
        //std::cerr << "TinyObjReader: " << reader.Error();
        spdlog::error("TinyObjReader {}", reader.Error());    
    }
    //return;
    }

    if (!reader.Warning().empty()) {
    std::cout << "TinyObjReader: " << reader.Warning();
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    std::vector<std::vector<std::shared_ptr<Shape>>> meshes;

    // Loop over shapes
    std :: cout << "Shape size : " << shapes.size() << "\n";
    //meshes.reserve(shapes.size());

    for (const auto & shape : shapes) {

        size_t index_offset = 0;

        // Loop over faces(polygon)
        std::vector<std::shared_ptr<Shape>> Triangles;
        
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            auto fv = size_t(shape.mesh.num_face_vertices[f]);

            Point tVertices[3];
            Point tNormals[3];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {

                // access to vertex
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) +0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) +1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) +2];
                //vertices.push_back(Vec3f(vx, vy, vz));
                tVertices[v] = Point(vx, vy, vz);

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
                    tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
                    tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];
                    tNormals[v] = Point(nx, ny, nz);
                }
                else{
                    tNormals[v] = Point(0,0,0);
                }
            }

            auto mat = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
            Triangles.push_back(std::make_shared<Triangle>(tVertices[0], tVertices[1], tVertices[2], mat));
            index_offset += fv;
        }
        meshes.push_back(Triangles);
    }

    return meshes;
}

*/