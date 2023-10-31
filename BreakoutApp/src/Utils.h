#pragma once

#include <vector>
#include <list>
#include <forward_list>

#include <SDL.h>

#include "GameData.h"
#include "Vec2.h"
#include "MeshRect.h"

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

    // generates positions for all of the obstacles, filling the box size
    // boxSize / obstacleSize must give a clean number
    std::vector<Vec2d> generatePositions(int numPositions, const Vec2d& obstacleSize, const Vec2d& boxSize);

}
