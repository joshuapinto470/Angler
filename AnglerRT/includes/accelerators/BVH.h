#pragma once

#include <algorithm>

#include "AnglerRT.h"
#include "Shape.h"
#include "Scene.h"
#include "Bounds.h"


class BVH : public Shape{
public:
    BVH(const Scene& scene, Float time0, Float time1):
        BVH(scene.GetObjects(), 0, scene.GetObjectsSize(), time0, time1) {}
    
    BVH(const std::vector<std::shared_ptr<Shape>>&, 
        size_t, size_t, Float, Float);
    
    virtual bool Hit(const Ray&, Float, Float, Interaction&) const override;
    virtual bool Bound(Float, Float, Bounds3&) const override;

private:
    std::shared_ptr<Shape> left;
    std::shared_ptr<Shape> right;
    Bounds3 box;
};

inline bool box_compare(const std::shared_ptr<Shape>, const std::shared_ptr<Shape>, int);
bool box_x_compare (const std::shared_ptr<Shape>, const std::shared_ptr<Shape>);
bool box_y_compare (const std::shared_ptr<Shape>, const std::shared_ptr<Shape>);
bool box_z_compare (const std::shared_ptr<Shape>, const std::shared_ptr<Shape>);