#pragma once

#include "Vec2.h"

struct MeshRect {
    Vec2d position;
    Vec2d size;

    MeshRect() : position(), size() {}
    MeshRect(Vec2d pos, Vec2d size) : position(pos), size(size) {}
};

struct MoveableMRect {
    MeshRect mRect;
    Vec2d velocity;
    double maxVelocity;

    MoveableMRect() : mRect(), velocity(), maxVelocity() {}
    MoveableMRect(MeshRect mRect, Vec2d vel, double maxVel) : mRect(mRect), velocity(vel), maxVelocity(maxVel) {}
};
