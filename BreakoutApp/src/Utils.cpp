#include "Utils.h"

#include <cmath>
#include <random>
#include <sstream>

#include "Logger.h"

// TODO regroup logic for different purposes
// regroup conversion functions into casts on structs

int Utils::roundDtoI(double a)
{
    return static_cast<int>(a + 0.5f);
}

Vec2i Utils::convVec(const Vec2d& vecD)
{
    Vec2i vecI = {
        Utils::roundDtoI(vecD.x),
        Utils::roundDtoI(vecD.y)
    };

    return vecI;
}

SDL_Rect Utils::convMeshRect(const MeshRect& mRect)
{
    SDL_Rect rect = {
        Utils::roundDtoI(mRect.position.x),
        Utils::roundDtoI(mRect.position.y),
        Utils::roundDtoI(mRect.size.x),
        Utils::roundDtoI(mRect.size.y)
    };

    return rect;
}

std::vector<Vec2d> Utils::generatePositions(int numPositions, const Vec2d& obstacleSize, const Vec2d& boxSize)
{
    std::vector<Vec2d> positionHolder(numPositions);

    Vec2d startPosition(obstacleSize.x / 2.f, boxSize.y - obstacleSize.y / 2.f);
    int numColumns = static_cast<int>(boxSize.x/obstacleSize.x);
    int numRows = (numPositions + numColumns - 1) / numColumns; // rounds up if both numbers are positive


    // TODO center box in x direction if size does not divide cleanly into boxSize
    int index = 0;
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numColumns && index < numPositions; ++j)
        {
            positionHolder[index] = Vec2d(startPosition.x + obstacleSize.x * j - boxSize.x / 2.f
                , startPosition.y - obstacleSize.y * i - boxSize.y / 2.f);

            index++;
        }
    }

    return positionHolder;
}
