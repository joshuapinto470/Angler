#pragma once

template <typename T>
class Bounds3{
private:
    Vec3<T> pMin, pMax;
};

template <typename T>
class Bounds2{
private:
    Vec2<T> pMin, pMax;
};