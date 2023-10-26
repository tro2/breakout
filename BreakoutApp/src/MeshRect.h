#pragma once

// TODO check that this needs to be a Vec2d, can it be forward declaration
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

    MoveableMRect() : mRect(), velocity() {}
    MoveableMRect(MeshRect mRect, Vec2d vel) : mRect(mRect), velocity(vel) {}
};
