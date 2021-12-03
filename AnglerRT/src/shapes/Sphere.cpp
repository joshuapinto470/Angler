#include "Sphere.h"

bool Sphere::Hit(const Ray &ray, Float t_min, Float t_max, Interaction &inter) const {

    Vec3f oc = ray.Origin() - mCenter;
    Float a = ray.Direction().LengthSquared();
    Float half_b = oc.dot(ray.Direction());
    Float c = oc.dot(oc) - mRadius * mRadius;
    Float discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    Float a_inv = 1.0f / a;

    Float sqrtd = sqrt(discriminant);
    Float root = (-half_b - sqrtd) * a_inv;

    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) * a_inv;
        if (root < t_min || t_max < root)
            return false;
    }

    inter.t = root;
    inter.hitLocation = ray.at(root);
    inter.set_face_normal(ray, (inter.hitLocation - mCenter) / mRadius);
    inter.material = material;
    /*
    BTW, Do we have to calculate the normal for every object?
    */
    return true;
}

bool Sphere::Bound(Float time0, double time1, Bounds3 &output_box) const {
    output_box = Bounds3(mCenter - Vec3d(mRadius, mRadius, mRadius), mCenter + Vec3d(mRadius, mRadius, mRadius));
    return true;
}