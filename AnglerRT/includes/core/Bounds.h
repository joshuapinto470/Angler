#pragma once
#include "Ray.h"
#include "Utilities.h"

class Bounds3 {
  public:
    Bounds3(){};
    Bounds3(const Point &a, const Point &b) {
        minimum = a;
        maximum = b;
    }

    bool hit(const Ray &ray, Float t_min, Float t_max) const {
        for (int a = 0; a < 3; a++) {
            Float invD = 1.0 / ray.Direction()[a];
            auto t0 = (minimum[a] - ray.Origin()[a]) * invD;
            auto t1 = (maximum[a] - ray.Origin()[a]) * invD;

            if (invD < 0.0f)
                std::swap(t0, t1);

            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;

            if (t_max <= t_min)
                return false;
        }
        return true;
    }

    Point min() {
        return minimum;
    };
    Point max() {
        return maximum;
    };

  private:
    Point maximum, minimum;
};
