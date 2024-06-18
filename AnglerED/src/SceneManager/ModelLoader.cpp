#include <ModelLoader.h>

#ifndef USE_ASSIMP
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#endif

using DS::Vertex;

#ifdef USE_ASSIMP

#include <stb/stb_image.h>

inline glm::vec3 aiVec3_to_glm(aiVector3D &vec)
{
    return {vec.x, vec.y, vec.z};
}

inline glm::vec2 aiVec3_to_glm2(aiVector3D &vec)
{
    return {vec.x, vec.y};
}

inline glm::mat4 aiMat4_to_glmMat4(const aiMatrix4x4 &aiMat)
{
    return {aiMat.a1, aiMat.b1, aiMat.c1, aiMat.d1, aiMat.a2, aiMat.b2, aiMat.c2, aiMat.d2,
            aiMat.a3, aiMat.b3, aiMat.c3, aiMat.d3, aiMat.a4, aiMat.b4, aiMat.c4, aiMat.d4};
}

inline meshNode aiNode_to_meshNode(const aiNode *node)
{
    meshNode _n;
    _n.m_transformation = aiMat4_to_glmMat4(node->mTransformation);
    for (unsigned i = 0; i < node->mNumMeshes; i++)
    {
        _n.m_meshIndices.push_back(node->mMeshes[i]);
    }

    return _n;
}

GLuint TextureFromFile(const char *path, const std::string &directory)
{
    BENCHMARK_SCOPE
    std::string filename = std::string(path);
    filename = directory + '/' + filename;
    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (!data)
        spdlog::warn("AssimpLoader Could not load texture!");
    GLuint id = GLEngine::generateTexture(data, width, height, nrComponents);
    stbi_image_free(data);
    return id;
}

MeshData AssimpLoader::loadMesh(const aiMesh *mesh)
{
    BENCHMARK_SCOPE
    MeshData data;
    data.m_vertices.reserve(mesh->mNumVertices);
    data.m_indices.reserve(mesh->mNumFaces * 3);

    // Load mesh vertex data
    for (unsigned j = 0; j < mesh->mNumVertices; j++)
    {
        Vertex vert{};

        vert.Position = aiVec3_to_glm(mesh->mVertices[j]);
        vert.Normals = mesh->HasNormals() ? aiVec3_to_glm(mesh->mNormals[j]) : glm::vec3(0.0f);
        vert.uv = mesh->mTextureCoords[0] ? aiVec3_to_glm2(mesh->mTextureCoords[0][j]) : glm::vec2(0.0f);

        data.m_vertices.push_back(vert);
    }

    // Load mesh index data
    for (unsigned int j = 0; j < mesh->mNumFaces; j++)
    {
        aiFace face = mesh->mFaces[j];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int k = 0; k < face.mNumIndices; k++)
        {
            data.m_indices.push_back(face.mIndices[k]);
        }
    }

    return data;
}

GLEngine::MaterialData AssimpLoader::loadMaterial(aiMaterial *material)
{
    BENCHMARK_SCOPE
    aiString name = material->GetName();

    // If the material is already loaded return it.
    for (auto & m_material : m_materials)
    {
        if (strcmp(name.C_Str(), m_material.name.c_str()) == 0)
        {
            return m_material;
        }
    }

    GLEngine::MaterialData mat;
    mat.name = name.C_Str();
    mat.diffuse = glm::vec3(0.1f);
    aiColor3D diffuse_color;
    material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse_color);
    mat.diffuse.r = diffuse_color.r;
    mat.diffuse.g = diffuse_color.g;
    mat.diffuse.b = diffuse_color.b;

    // Load Diffuse Maps
    aiTextureType type = aiTextureType_DIFFUSE;

    for (unsigned j = 0; j < material->GetTextureCount(type); j++)
    {
        aiString path;
        material->GetTexture(type, j, &path);

        bool textureLoaded = false;
        for (auto & m_texture : m_textures)
        {
            if (strcmp(m_texture.path.c_str(), path.C_Str()) == 0)
            {
                textureLoaded = true;
                mat.m_textures.push_back(m_texture);
                break;
            }
        }

        if (!textureLoaded)
        {
            GLEngine::Texture texture;
            texture.id = TextureFromFile(path.C_Str(), m_directory);
            texture.path = path.C_Str();
            texture.type = "mat_diffuse";
            m_textures.push_back(texture);
            mat.m_textures.push_back(texture);
        }
    }

    return mat;
}

MeshNode *deepCopy(aiNode *node)
{
    meshNode m = aiNode_to_meshNode(node);
    auto *_node = new MeshNode(m);

    _node->setName(node->mName.C_Str());

    for (int i = 0; i < node->mNumChildren; i++)
    {
        aiNode *n = node->mChildren[i];
        _node->addChild(deepCopy(n));
    }

    return _node;
}

Model AssimpLoader::LoadModel(std::string path)
{
    BENCHMARK_SCOPE

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                                                       aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        spdlog::warn("File Reader {}", importer.GetErrorString());
        return {};
    }

    m_directory = path.substr(0, path.find_last_of('/'));

    // Process all the meshes in the scene first
    m_meshes.clear();
    m_meshes.reserve(scene->mNumMeshes);
    for (unsigned i = 0; i < scene->mNumMeshes; i++)
    {
        GLMesh _mesh;
        aiMesh *a_mesh = scene->mMeshes[i];
        MeshData data = loadMesh(a_mesh);
        _mesh.m_mesh = data;
        _mesh.m_name = a_mesh->mName.C_Str();
        _mesh.m_material = a_mesh->mMaterialIndex;
        m_meshes.push_back(_mesh);
    }

    // Process all the materials in the scene.
    for (unsigned i = 0; i < scene->mNumMaterials; i++)
    {
        aiMaterial *material = scene->mMaterials[i];
        m_materials.emplace_back(loadMaterial(material));
    }

    if (scene->HasCameras())
    {
        for (unsigned i = 0; i < scene->mNumCameras; i++)
        {
            aiCamera *cam = scene->mCameras[i];
            spdlog::info("ModelLoader Camera : {}", cam->mName.C_Str());
            glm::vec3 pos = aiVec3_to_glm(cam->mPosition);
            glm::vec3 lookAt = aiVec3_to_glm(cam->mLookAt);
            spdlog::info("ModelLoader Position : {}, {}, {}", pos.x, pos.y, pos.z);
            spdlog::info("ModelLoader LookAt : {}, {}, {}", lookAt.x, lookAt.y, lookAt.z);
        }
    }

    // Create the scene hierarchy
    std::shared_ptr<MeshNode> root(deepCopy(scene->mRootNode));

    MeshFilter meshes;
    meshes.m_meshes = m_meshes;

    Model model;
    model.m_mesh = meshes;
    model.m_root = root;
    model.m_materials = m_materials;
    model.m_textures = m_textures;

    spdlog::info("ModelLoader - Total Meshes: {}", meshes.m_meshes.size());
    spdlog::info("ModelLoader - Total Materials: {}", m_materials.size());
    spdlog::info("ModelLoader - Total Textures: {}", m_textures.size());

    return model;
}

#else
Model ObjLoader::LoadModel(std ::string path)
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

    MeshFilter meshRef;

    std::vector<GLMesh> meshes;

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
                // vertex.Diffuse = glm::vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
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

        std::shared_ptr<MeshData> data = std::make_shared<MeshData>();
        data->m_vertices = vertices;
        data->m_indices = indices;

        GLMesh M;
        M.m_mesh = data;
        M.m_name = shape.name;

        meshes.push_back(M);
    }

    MeshFilter model;
    model.m_meshes = meshes;

    return Model(model);
}
#endif
