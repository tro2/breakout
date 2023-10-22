#pragma once

struct Vec2d {
    double x;
    double y;

    Vec2d() : x(0.f), y(0.f) {}
    Vec2d(double x, double y) : x(x), y(y) {}
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

struct Paddle {
    MeshRect paddleRect;
    Vec2d velocity;

    Paddle() : paddleRect(), velocity() {}
    Paddle(MeshRect mRect, Vec2d vel) : paddleRect(mRect), velocity(vel) {}
};

struct Ball {
    MeshRect ballRect;
    Vec2d velocity;

    Ball() : ballRect(), velocity() {}
    Ball(MeshRect mRect, Vec2d vel) : ballRect(mRect), velocity(vel) {}
};

enum GameState
{
    READY,
    IN_GAME,
    VICTORY,
};

enum PaddleMove
{
    STILL,
    LEFT,
    RIGHT
};
