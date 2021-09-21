#pragma once

#include "Shape.h"
#include "Triangle.h"


class Plane : public Shape{
    private:
        Point A, B, C, D;
        Triangle X, Y;
        std :: shared_ptr<Material> material;
    public:
        Plane() = default;
        Plane(Point a, Point b, Point c, Point d, const std::shared_ptr<Material>& mat) : A(a),
        B(b), C(c), D(d), material(mat),
        X(A, C, B, mat),
        Y(B, C, D, mat){};

        bool Hit(const Ray&, Float, Float, Interaction&) const override;
        bool Bound(Float time0, double time1, Bounds3& output_box) const override;
};