#pragma once

#include "Vec2.h"

struct MeshRect {
    Vec2<float> position;
    Vec2<float> size;

    MeshRect() : position(), size() {}
    MeshRect(Vec2<float> pos, Vec2<float> size) : position(pos), size(size) {}
};

struct MoveableMRect {
    MeshRect mRect;
    Vec2<float> velocity;
    float maxVelocity;

    MoveableMRect() : mRect(), velocity(), maxVelocity() {}
    MoveableMRect(MeshRect mRect, Vec2<float> vel, float maxVel) : mRect(mRect), velocity(vel), maxVelocity(maxVel) {}
};
