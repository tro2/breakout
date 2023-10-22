#include "Utils.h"
#include <cmath>
#include <random>

double Utils::randomDouble(double lowerBound, double upperBound)
{
    // random device for randomization functions
    static std::random_device rand;

    // randomization engine
    static std::default_random_engine eng(rand());

    std::uniform_real_distribution<double> distr(lowerBound, upperBound);

    return distr(eng);
}

int Utils::randomInt(int lowerBound, int upperBound)
{
    // random device for randomization functions
    static std::random_device rand;

    // randomization engine
    static std::default_random_engine eng(rand());

    std::uniform_int_distribution<int> distr(lowerBound, upperBound);

    return distr(eng);
}

int Utils::preciseAdd(int a, double b)
{
    double preciseA = a;
    preciseA += b;

    return static_cast<int>(round(preciseA));
}

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

Vec2d Utils::scaleVecD(const Vec2d& vecD, double scalar)
{
    return { vecD.x * scalar, vecD.y * scalar };
}

Vec2i Utils::scaleVecI(const Vec2i& vecI, float scalar)
{
    return { Utils::roundDtoI(vecI.x * scalar), Utils::roundDtoI(vecI.y * scalar) };
}
