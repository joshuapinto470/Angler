#pragma once

#include <utility>

#include "Shape.h"

/*
   
  A->   /\
       /  \
      /    \
     /      \
B->  --------  <- C
*/

/*
The triangle shape is defined in a counter clockwise direction
where A is the top vertex.
      B is the bottom left vertex.
      C is the bottom right vertex.
*/

struct TriangleMesh{
        int nTriangles;
        std::unique_ptr<Vec3f[]> vertices;
        std::unique_ptr<Vec3f[]> normals;

        std::vector<int> vertexIndices;
        //TriangleMesh(std::vector<Vec3f>, std::vector<Vec3f>, int*, int);
};

class Triangle : public Shape{
    private:
        Point A, B, C;
        std :: shared_ptr<Material> material;
    public:
        Triangle() = default;
        Triangle(Point Top, Point Left, Point Right, std :: shared_ptr<Material> mat) : 
        A(Top),
        B(Left),
        C(Right),
        material(mat)
        {};

        bool Hit(const Ray&, Float, Float, Interaction&) const override;
};

// std::vector<std::shared_ptr<Shape>> CreateTriangleMesh(float* v, float* n, int* vi, int nTriangles){

//     std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>(v, n, vi, nTriangles);
//     std::vector<std::shared_ptr<Shape>> tris;
//     tris.reserve(nTriangles);

//     for(int s = 0; s < nTriangles; s++){
//         tris.push_back(std::make_shared<Triangle>());
//     }

// } 