#pragma once

#include <random>
#include "Utilities.h"

inline Float random_double(){
    static std :: uniform_real_distribution<double> distribution(0.0, 1.0);
    static std :: mt19937 generator;
    return distribution(generator);
}

inline Float random_double(Float min, Float max){
    return min + (max - min) * random_double();
}

inline int random_int(int min, int max){
    return static_cast<int>(random_double(min, max+1));
}

inline Color random_color(){
    return Color(random_double(), random_double(), random_double());
}

inline Vec3f random_vector(){
    return {random_double(), random_double(), random_double()};
}

inline Vec3f random_vector(Float min, Float max){
    return {random_double(min, max), random_double(min, max), random_double(min, max)};
}

inline Vec3f random_in_unit_sphere(){
    /* THIS FUNCTION IS NOT EFFICIENT..
       THIS IS JUST temporary */
    while(true){
        auto p = random_vector(-1, 1);
        if(p.LengthSquared() >= 1) continue;
        return p;
    }
}

inline Vec3f random_unit_vector(){
    return random_in_unit_sphere().Normalize();
} 