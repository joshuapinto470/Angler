#pragma once

#include <Mesh.h>

class Model
{
private:
    std::vector<Mesh> m_mesh;

public:
    Model() = default;
    Model(std::vector<Mesh>);
    void PrintModelInfo();
    void Draw();
    void initModel();
    ~Model() {}
};