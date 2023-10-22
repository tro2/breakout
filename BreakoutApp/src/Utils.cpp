#include "Utils.h"

#include <cmath>
#include <random>

#include "Logger.h"

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

//SDL_Rect Utils::convMeshRect(const MeshRect& mRect)
//{
//    SDL_Rect rect = {
//        Utils::roundDtoI(mRect.position.x),
//        Utils::roundDtoI(mRect.position.y),
//        Utils::roundDtoI(mRect.size.x),
//        Utils::roundDtoI(mRect.size.y)
//    };
//
//    return rect;
//}

Vec2d Utils::calcElasticBounce(MoveableMRect& ball, const MeshRect& obstacle)
{
    return { 0.f,0.f };
}


Vec2d Utils::calcStaticBounce(MoveableMRect& paddle, const MeshRect& obstacle)
{
    // update paddle position
    // paddle to the right of the object
    if (paddle.velocity.x > 0)
    {
        paddle.mRect.position.x = obstacle.position.x - obstacle.size.x / 2.f - paddle.mRect.size.x / 2.f;
    }
    // paddle is to the left
    else if (paddle.velocity.x < 0)
    {
        // paddle.x - paddlesize.x / 2 = obstacle.x + obstaclesize.x / 2
        paddle.mRect.position.x = obstacle.position.x + obstacle.size.x / 2.f + paddle.mRect.size.x / 2.f;
    }

    return { 0.f,0.f };
}

bool Utils::checkCollision(const MeshRect& a, const MeshRect& b)
{
    // the sides to check collisions
    double leftA;
    double rightA;
    double topA;
    double bottomA;

    double leftB;
    double rightB;
    double topB;
    double bottomB;

    // Calculate the sides of rect A
    leftA = a.position.x - a.size.x / 2.f;
    rightA = a.position.x + a.size.x / 2.f;
    topA = a.position.y + a.size.y / 2.f;
    bottomA = a.position.y - a.size.y / 2.f;

    // Calculate the sides of rect B
    leftB = b.position.x - b.size.x / 2.f;
    rightB = b.position.x + b.size.x / 2.f;
    topB = b.position.y + b.size.y / 2.f;
    bottomB = b.position.y - b.size.y / 2.f;

    // if x bounds don't overlap
    if (rightA < leftB 
        || leftA > rightB)
    {
        return false;
    }

    // if y bounds don't overlap
    if (bottomA > topB
        || topA < bottomB)
    {
        return false;
    }

    // do overlap in both dimensions
    return true;
}

void Utils::moveElasticBounce(MoveableMRect& object, std::vector<MeshRect*> objectArr, double timeStep)
{
    return;
}

void Utils::moveStaticBounce(MoveableMRect& object, std::vector<MeshRect*> objectArr, double timeStep)
{
    Vec2d oldPosition = object.mRect.position;

    object.mRect.position += object.velocity * timeStep;

    for (auto it = objectArr.begin(); it != objectArr.end(); ++it)
    {
        if (checkCollision(object.mRect, **it))
        {
            Utils::calcStaticBounce(object, **it);

            // TODO need to loop until all possible collisions are resolved
        }
    }
}
