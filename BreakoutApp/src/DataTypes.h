#pragma once

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
        return Vec2d(x*s, y*s);
    }
};

struct Vec2i {
    int x;
    int y;

    Vec2i() : x(0), y(0) {}
    Vec2i(int x, int y) : x(x), y(y) {}
};

struct MeshRect {
    Vec2d position;
    Vec2d size;

    MeshRect() : position(), size() {}
    MeshRect(Vec2d pos, Vec2d size) : position(pos), size(size) {}
};

struct MoveableMRect {
    MeshRect mRect;
    Vec2d velocity;

    MoveableMRect() : mRect(), velocity() {}
    MoveableMRect(MeshRect mRect, Vec2d vel) : mRect(mRect), velocity(vel) {}
};

enum GameState
{
    READY,
    IN_GAME,
    VICTORY,
};

enum PaddleMove
{
    LEFT,
    STILL,
    RIGHT
};
