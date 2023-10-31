#pragma once

#include <cmath>

// 2D vector of doubles
struct Vec2d {
    double x;
    double y;

    Vec2d() : x(0.f), y(0.f) {}
    Vec2d(double x, double y) : x(x), y(y) {}

    Vec2d& operator +=(const Vec2d& v)
    {
        x += v.x;
        y += v.y;
        return (*this);
    }

    Vec2d& operator -=(const Vec2d& v)
    {
        x -= v.x;
        y -= v.y;
        return (*this);
    }

    Vec2d& operator *=(double s)
    {
        x *= s;
        y *= s;
        return (*this);
    }

    Vec2d operator *(double s) const
    {
        return Vec2d(x * s, y * s);
    }

    Vec2d operator *(const Vec2d& v) const
    {
        return Vec2d(x * v.x, y * v.y);
    }

    double magnitude() const
    {
        return static_cast<double>(sqrt(x * x + y * y));
    }
};

// 2D vector of ints
struct Vec2i {
    int x;
    int y;

    Vec2i() : x(0), y(0) {}
    Vec2i(int x, int y) : x(x), y(y) {}
};
