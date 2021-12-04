#pragma once

#define deg2rad 0.017453292519943295
#define rad2deg 57.29577951308232

#include <cmath>
#include <iostream>
#include <spdlog/spdlog.h>

template <typename T> class Mat44 {
  private:
    T data[4][4];

  public:
    explicit Mat44<T>(T[4][4]);
    Mat44<T>();

    T det();
    Mat44<T> inverse();

    float &operator[](int i) {
        return data[i];
    }
    float operator[](int i) const {
        return data[i];
    }
    Mat44<T> operator*(float);
    Mat44<T> operator*(Mat44<T>);
    bool operator==(Mat44<T>);
};

template <typename T> Mat44<T>::Mat44(T d[][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            data[i][j] = d[i][j];
}

template <typename T> Mat44<T>::Mat44() {
    data = { 0 };
}

template <typename T> bool Mat44<T>::operator==(Mat44<T> M) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (M[i][j] != data[i][j])
                return false;
    return true;
}

template <typename T> Mat44<T> Mat44<T>::operator*(float scale) {
    float x[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            x[i][j] = data[i][j] * scale;
        }
    }
    Mat44 mat(x);
    return mat;
}

template <typename T> Mat44<T> Mat44<T>::operator*(Mat44<T> M) {
    Mat44 mul;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += M[i][k] * data[k][j];
            }
            mul[i][j] = sum;
        }
    }

    return mul;
}

template <typename T> T Mat44<T>::det() {
    T m1 = data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
           data[1][2] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) +
           data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]);

    T m2 = data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
           data[1][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
           data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]);

    T m3 = data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) -
           data[1][1] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
           data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);

    T m4 = data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) -
           data[1][1] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]) +
           data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);

    T detm = (data[0][0] * m1) - (data[0][1] * m2) + (data[0][2] * m3) - (data[0][3] * m4);
    return detm;
}

template <typename T> Mat44<T> Mat44<T>::inverse() {
    float adj[4][4];
    float M[3][3];

    float d = det();
    if (d == 0)
        return *this;

    d = 1.0f / d;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Get the co-factor matrix of i,j
            int x = 0, y = 0;
            for (int row = 0; row < 4; row++) {
                for (int column = 0; column < 4; column++) {
                    if ((i == row) || (j == column)) {
                        continue;
                    }
                    M[x][y++] = data[row][column];
                }
                if (y > 0) {
                    y = 0;
                    x++;
                }
            }

            float det_sub = M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
                            M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) +
                            M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);

            adj[j][i] = (float)pow(-1, i + j) * det_sub;
        }
    }

    Mat44 mat(adj);
    return mat * d;
}

// Vec3 CLASS

template <typename T> class Vec3 {
  private:
    T _x, _y, _z;

  public:
    Vec3<T>(T x, T y, T z) : _x(x), _y(y), _z(z){};
    Vec3<T>() : _x(0), _y(0), _z(0){};

    T dot(const Vec3<T> &) const;
    Vec3<T> cross(const Vec3<T> &);
    Vec3<T> Normalize();
    inline double Length();
    inline double LengthSquared();

    inline T x() const {
        return _x;
    };
    inline T y() const {
        return _y;
    };
    inline T z() const {
        return _z;
    };

    Vec3<T> operator+(const Vec3<T> &);
    Vec3<T> operator/(double);
    Vec3<T> operator-(const Vec3<T> &);
    Vec3<T> operator-() const;
    T operator[](int &) const;

    void Print() {
        std ::cout << "< " << _x << ", " << _y << ", " << _z << " >\n";
    };
};

template <typename T> inline Vec3<T> Vec3<T>::operator+(const Vec3<T> &v) {
    return Vec3<T>(_x + v._x, _y + v._y, _z + v._z);
}

template <typename T> inline T Vec3<T>::operator[](int &a) const {
    if (a == 0)
        return _x;
    if (a == 1)
        return _y;
    if (a == 2)
        return _z;

#ifndef NDEBUG
    spdlog::warn("Vector component out of range!");
#endif
    return _z;
}

template <typename T> inline Vec3<T> Vec3<T>::operator-(const Vec3<T> &v) {
    return Vec3<T>(_x - v._x, _y - v._y, _z - v._z);
}

template <typename T> inline Vec3<T> Vec3<T>::operator/(double v) {
    return *this * (1.0 / v);
    // return Vec3<T>(_x * v, _y * v, _z * v);
}

template <typename T> inline Vec3<T> Vec3<T>::operator-() const {
    return Vec3<T>(-_x, -_y, -_z);
}

template <typename T> inline T Vec3<T>::dot(const Vec3<T> &v) const {
    return _x * v._x + _y * v._y + _z * v._z;
}

template <typename T> Vec3<T> Vec3<T>::cross(const Vec3<T> &v) {
    float x = _y * v._z - _z * v._y;
    float y = _z * v._x - _x * v._z;
    float z = _x * v._y - _y * v._x;
    return Vec3<T>(x, y, z);
}

template <typename T> inline double Vec3<T>::Length() {
    return (double)sqrt(_x * _x + _y * _y + _z * _z);
}

template <typename T> inline double Vec3<T>::LengthSquared() {
    return (double)_x * _x + _y * _y + _z * _z;
}

template <typename T> Vec3<T> Vec3<T>::Normalize() {
#ifndef NDEBUG
    if (Length() != 0) {
        double _len = 1 / Length();
        return Vec3<T>(_x * _len, _y * _len, _z * _len);
    }

    return Vec3<T>(0, 0, 0);
#endif

    double _len = 1 / Length();
    return Vec3<T>(_x * _len, _y * _len, _z * _len);
}

// Utility functions for Vec3

template <typename T> inline const Vec3<T> operator*(double v, const Vec3<T> &u) {
    return Vec3<T>(u.x() * v, u.y() * v, u.z() * v);
}

template <typename T> inline Vec3<T> operator*(const Vec3<T> &u, double v) {
    return v * u;
}

template <typename T, typename J> inline Vec3<T> operator*(const Vec3<T> &u, const Vec3<J> &v) {
    return Vec3<T>(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

template <typename T> inline Vec3<T> operator-(double v, const Vec3<T> &u) {
    return Vec3<T>(u.x() - v, u.y() - v, u.z() - v);
}

template <typename T> inline Vec3<T> operator-(const Vec3<T> &u, double v) {
    return v - u;
}

template <typename T, typename J> inline Vec3<T> operator-(const Vec3<T> &u, const Vec3<J> &v) {
    return Vec3<T>(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

template <typename T> inline Vec3<T> operator+(double v, const Vec3<T> &u) {
    return Vec3<T>(u.x() + v, u.y() + v, u.z() + v);
}

template <typename T> inline Vec3<T> operator+(const Vec3<T> &u, double v) {
    return v + u;
}

template <typename T, typename J> inline Vec3<T> operator+(const Vec3<T> &u, const Vec3<J> &v) {
    return Vec3<T>(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

// Vec2 Class

template <typename T> class Vec2 {
  private:
    T _x, _y;

  public:
    Vec2<T>(T x, T y) : _x(x), _y(y){};
    Vec2<T>() : _x(0), _y(0){};

    T dot(const Vec2<T> &) const;
    Vec2<T> Normalize();
    inline double Length();
    inline double LengthSquared();

    inline T x() const {
        return _x;
    };
    inline T y() const {
        return _y;
    };

    Vec2<T> operator+(const Vec2<T> &);
    Vec2<T> operator/(double);
    Vec2<T> operator-(const Vec2<T> &);
    Vec2<T> operator-() const;

    void Print() {
        std ::cout << "< " << _x << ", " << _y << " >\n";
    };
};

template <typename T> inline Vec2<T> Vec2<T>::operator+(const Vec2<T> &v) {
    return Vec2<T>(_x + v._x, _y + v._y);
}

template <typename T> inline Vec2<T> Vec2<T>::operator-(const Vec2<T> &v) {
    return Vec2<T>(_x - v._x, _y - v._y);
}

template <typename T> inline Vec2<T> Vec2<T>::operator/(double v) {
    return *this * (1.0 / v);
    // return Vec3<T>(_x * v, _y * v, _z * v);
}

template <typename T> inline Vec2<T> Vec2<T>::operator-() const {
    return Vec2<T>(-_x, -_y);
}

template <typename T> inline T Vec2<T>::dot(const Vec2<T> &v) const {
    return _x * v._x + _y * v._y;
}

template <typename T> inline double Vec2<T>::Length() {
    return (double)sqrt(_x * _x + _y * _y);
}

template <typename T> inline double Vec2<T>::LengthSquared() {
    return (double)_x * _x + _y * _y;
}

template <typename T> Vec2<T> Vec2<T>::Normalize() {

#ifndef NDEBUG
    // Do a divide by zero check in debug mode.
    if (Length() != 0) {
        double _len = 1 / Length();
        return Vec2<T>(_x * _len, _y * _len);
    }

    // Safe return 0.
    spdlog::warn("Attempt divide by zero!");
    return Vec2<T>(0, 0);
#endif

    double _len = 1 / Length();
    return Vec2<T>(_x * _len, _y * _len);
}

// Utility functions for Vec3

template <typename T> inline const Vec2<T> operator*(double v, const Vec2<T> &u) {
    return Vec2<T>(u.x() * v, u.y() * v);
}

template <typename T> inline Vec2<T> operator*(const Vec2<T> &u, double v) {
    return v * u;
}

template <typename T, typename J> inline Vec2<T> operator*(const Vec2<T> &u, const Vec2<J> &v) {
    return Vec2<T>(u.x() * v.x(), u.y() * v.y());
}

template <typename T> inline Vec2<T> operator-(double v, const Vec2<T> &u) {
    return Vec2<T>(u.x() - v, u.y() - v);
}

template <typename T> inline Vec2<T> operator-(const Vec2<T> &u, double v) {
    return v - u;
}

template <typename T, typename J> inline Vec2<T> operator-(const Vec2<T> &u, const Vec2<J> &v) {
    return Vec2<T>(u.x() - v.x(), u.y() - v.y());
}

template <typename T> inline Vec2<T> operator+(double v, const Vec2<T> &u) {
    return Vec2<T>(u.x() + v, u.y() + v);
}

template <typename T> inline Vec2<T> operator+(const Vec2<T> &u, double v) {
    return v + u;
}

template <typename T, typename J> inline Vec2<T> operator+(const Vec2<T> &u, const Vec2<J> &v) {
    return Vec2<T>(u.x() + v.x(), u.y() + v.y());
}
