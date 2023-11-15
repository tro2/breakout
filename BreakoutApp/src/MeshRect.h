#pragma once

#include "Vec2.h"
#include <SDL.h>

struct MeshRect {
    Vec2<float> position;
    Vec2<float> size;

    MeshRect() : position(), size() {}
    MeshRect(Vec2<float> pos, Vec2<float> size) : position(pos), size(size) {}

    SDL_FRect castFRect() const
    {
        SDL_FRect fRect;

        fRect.x = position.x;
        fRect.y = position.y;
        fRect.w = size.x;
        fRect.h = size.y;
        
        return fRect;
    }
};

struct MoveableMRect {
    MeshRect mRect;
    Vec2<float> velocity;
    float maxVelocity;

    MoveableMRect() : mRect(), velocity(), maxVelocity() {}
    MoveableMRect(MeshRect mRect, Vec2<float> vel, float maxVel) : mRect(mRect), velocity(vel), maxVelocity(maxVel) {}
};
