#include "Triangle.h"

bool Triangle ::Hit(const Ray &ray, Float t_min, Float t_max, Interaction &inter) const {
    Vec3f E1 = B - A;
    Vec3f E2 = C - A;
    Vec3f N = E1.cross(E2);

    Float det = -ray.Direction().dot(N);
    Float invdet = 1.0 / det;
    Vec3f AO = ray.Origin() - A;
    Vec3f DAO = AO.cross(ray.Direction());

    Float u = E2.dot(DAO) * invdet;
    Float v = -E1.dot(DAO) * invdet;
    Float t = AO.dot(N) * invdet;

    if (det >= 1e-6 && t >= 0.0 && u >= 0.0 && v >= 0.0 && (u + v) <= 1.0) {
        if (t > t_min && t < t_max) {
            inter.t = t;
            inter.hitLocation = ray.at(t);
            inter.set_face_normal(ray, E1.cross(E2).Normalize());
            inter.material = material;
            return true;
        }
    }

    return false;
}

bool Triangle::Bound(Float time0, double time1, Bounds3 &output_box) const {
    return true;
}