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

    // custom function for accurate rounding of doubles to ints
    int roundDtoI(double a);

    Vec2<int> convVec(const Vec2<float>& vecD);

    SDL_Rect convMeshRect(const MeshRect& mRect);

    // generates positions for all of the obstacles, filling the box size
    // boxSize / obstacleSize must give a clean number
    std::vector<Vec2<float>> generatePositions(int numPositions, const Vec2<float>& obstacleSize, const Vec2<float>& boxSize);

}
