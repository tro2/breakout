#pragma once

#include <cmath>

// 2D vector of doubles
template <typename T>
struct Vec2 {
    T x;
    T y;

    Vec2() : x(0.f), y(0.f) {}
    Vec2(T x, T y) : x(x), y(y) {}

    Vec2& operator +=(const Vec2& v)
    {
        x += v.x;
        y += v.y;
        return (*this);
    }

    Vec2& operator -=(const Vec2& v)
    {
        x -= v.x;
        y -= v.y;
        return (*this);
    }

    Vec2 operator *(T s) const
    {
        return Vec2<float>(x * s, y * s);
    }

    Vec2& operator *=(T s)
    {
        x *= s;
        y *= s;
        return (*this);
    }

    // warning, division by 0 is undefined
    Vec2 operator /(T s) const
    {
        return Vec2<float>(x / s, y / s);
    }

    T magnitude() const
    {
        return static_cast<T>(sqrt(x * x + y * y));
    }

    // returns a unit vector in the direction of the referenced vector
    // returns 0 if magnitude of referenced vector is 0
    Vec2 unitVector() const
    {
        if (T magnitude = this->magnitude(); magnitude != 0.f)
        {
            return *this / magnitude;
        }

        return Vec2();
    }
};
