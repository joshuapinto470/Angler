#pragma once

#include "Ray.h"

class Material;


// Stores the surface interaction at the ray hit point.
struct Interaction{
    Point hitLocation;
    Vec3f Normal;
    Float t;
    std :: shared_ptr<Material> material;

    bool front_face;

    inline void set_face_normal(const Ray& ray, const Vec3f& out_normal){
        front_face = ray.Direction().dot(out_normal) < 0;
        Normal = front_face ? out_normal : -out_normal;
    }
};


class Shape{
    public :
        virtual bool Hit(const Ray&, Float, Float, Interaction&) const = 0;    
};