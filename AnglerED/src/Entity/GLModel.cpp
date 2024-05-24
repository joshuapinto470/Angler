#include <GLModel.h>

Model::Model(MeshFilter mesh, GLMaterial::Material material)
{
    m_mesh = mesh;
    m_material = material;
}

Model::Model(MeshFilter mesh)
{
    m_mesh = mesh;
}

GLMaterial::Material Model::getMaterial()
{
    return m_material;
}

MeshFilter Model::getMesh()
{
    return m_mesh;
}
