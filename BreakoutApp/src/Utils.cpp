#include "Utils.h"

#include <cmath>
#include <random>
#include <sstream>

#include "Logger.h"

// TODO regroup logic for different purposes
int Utils::roundDtoI(double a)
{
    return static_cast<int>(a + 0.5f);
}

Vec2<int> Utils::convVec(const Vec2<float>& vecD)
{
    return Vec2<int>(Utils::roundDtoI(vecD.x), Utils::roundDtoI(vecD.y));
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

MeshRect Utils::translateTopLeft(const MeshRect& mRect, const AppContext& app)
{
    // position is given relative to world origin in center and position marking center of mesh
    MeshRect mCopy = mRect;
    mCopy.position *= app.PIXELS_PER_UNIT;
    mCopy.size *= app.PIXELS_PER_UNIT;

    // conv pos to rect origin at top left
    mCopy.position.x -= mCopy.size.x / 2;
    mCopy.position.y += mCopy.size.y / 2;

    // conv pos to relative to top left
    mCopy.position.x = app.WINDOW_SIZE.x / 2 + mCopy.position.x;
    mCopy.position.y = app.WINDOW_SIZE.y / 2 - mCopy.position.y;

    return mCopy;
}

std::vector<Vec2<float>> Utils::generatePositions(int numPositions, const Vec2<float>& obstacleSize, const Vec2<float>& boxSize)
{
    std::vector<Vec2<float>> positionHolder(numPositions);

    Vec2<float> startPosition(obstacleSize.x / 2.f, boxSize.y - obstacleSize.y / 2.f);
    int numColumns = static_cast<int>(boxSize.x/obstacleSize.x);
    int numRows = (numPositions + numColumns - 1) / numColumns; // rounds up if both numbers are positive


    // TODO center box in x direction if size does not divide cleanly into boxSize
    int index = 0;
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numColumns && index < numPositions; ++j)
        {
            positionHolder[index] = Vec2<float>(startPosition.x + obstacleSize.x * j - boxSize.x / 2.f
                , startPosition.y - obstacleSize.y * i - boxSize.y / 2.f);

            index++;
        }
    }

    return positionHolder;
}
