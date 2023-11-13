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

    Vec2d operator *(double s) const
    {
        return Vec2d(x * s, y * s);
    }

    // warning, division by 0 is undefined
    Vec2d operator /(double s) const
    {
        return Vec2d(x / s, y / s);
    }

    double magnitude() const
    {
        return static_cast<double>(sqrt(x * x + y * y));
    }

    // returns a unit vector in the direction of the referenced vector
    // returns 0 if magnitude of referenced vector is 0
    Vec2d unitVector() const
    {
        if (double magnitude = this->magnitude(); magnitude != 0.f)
        {
            return *this / magnitude;
        }

        return Vec2d();
    }
};

// 2D vector of ints
struct Vec2i {
    int x;
    int y;

    Vec2i() : x(0), y(0) {}
    Vec2i(int x, int y) : x(x), y(y) {}
};
