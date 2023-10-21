#pragma once

#include <random>

#include <SDL.h>

#include "DataTypes.h"

namespace Utils
{
    // FUNCTIONS ================================

    // generates random double between lowerBound and upperBound
    double randomDouble(double lowerBound, double upperBound);

    // generates random int between lowerBound and upperBound
    int randomInt(int lowerBound, int upperBound);

    // adds and properly rounds int a and double b
    int preciseAdd(int a, double b);

    int roundDtoI(double a);

    Vec2i convVec(const Vec2d& vecD);

    SDL_Rect convMeshRect(const MeshRect& mRect);

    Vec2d scaleVecD(const Vec2d& vecD, double scalar);

    Vec2i scaleVecI(const Vec2i& vecI, float scalar);
}
