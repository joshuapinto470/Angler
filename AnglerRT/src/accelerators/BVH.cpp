#include "BVH.h"

bool BVH::Bound(Float time0, Float time1, Bounds3& output_box) const{
    output_box = box;
    return true;
}

bool BVH::Hit(const Ray& r, Float t_min, Float t_max, Interaction& inter) const{
    if(!box.hit(r, t_min, t_max))
        return false;
    
    bool hit_left = left->Hit(r, t_min, t_max, inter);
    bool hit_right = right->Hit(r, t_min, hit_left ? inter.t : t_max, inter);

    return hit_left || hit_right;
}

BVH::BVH(
    const std::vector<std::shared_ptr<Shape>>& src_objects,
    size_t start, size_t end, Float time0, Float time1
) {
    //spdlog::info("Creating BVH node.");

    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = random_int(0,2);
    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left = right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        } else {
            left = objects[start+1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        left = std::make_shared<BVH>(objects, start, mid, time0, time1);
        right = std::make_shared<BVH>(objects, mid, end, time0, time1);
    }

    Bounds3 box_left, box_right;

    if (  !left->Bound (time0, time1, box_left)
       || !right->Bound(time0, time1, box_right)
    )
        spdlog::warn("No bounding box in bvh_node constructor.");

    box = Union(box_left, box_right);
}

inline bool box_compare(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b, int axis) {
    Bounds3 box_a;
    Bounds3 box_b;

    if (!a->Bound(0,0, box_a) || !b->Bound(0,0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.min()[axis] < box_b.min()[axis];
}


bool box_x_compare (const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
    return box_compare(a, b, 0);
}

bool box_y_compare (const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
    return box_compare(a, b, 1);
}

bool box_z_compare (const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
    return box_compare(a, b, 2);
}