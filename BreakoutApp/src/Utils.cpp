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

Vec2d Utils::calcElasticBounce(MoveableMRect& mObject, const MeshRect& obstacle)
{
    // determine direction of movement
    int directionX = (mObject.velocity.x > 0) ? -1 : 1;
    int directionY = (mObject.velocity.y > 0) ? -1 : 1;

    // figure out how much to move back in x direction
    double moveBackX = 0.f;
    if (mObject.velocity.x != 0)
    {
        moveBackX = (obstacle.size.x / 2.f + mObject.mRect.size.x / 2.f) * directionX;
        mObject.mRect.position.x = obstacle.position.x + moveBackX;
    }

    // figure out how much to move back in y direction
    double moveBackY = 0.f;
    if (mObject.velocity.y != 0)
    {
        moveBackY = (obstacle.size.y / 2.f + mObject.mRect.size.y / 2.f) * directionY;
        mObject.mRect.position.y = obstacle.position.y + moveBackY;
    }

    // update velocity
    mObject.velocity.x *= -1;
    mObject.velocity.y *= -1;
    
    return { moveBackX,moveBackY };
}


Vec2d Utils::calcStaticBounce(MoveableMRect& mObject, const MeshRect& obstacle)
{
    /*
    // update mObject position
     mObject to the right of the mObject
    if (mObject.velocity.x > 0)
    {
        mObject.mRect.position.x = obstacle.position.x - obstacle.size.x / 2.f - mObject.mRect.size.x / 2.f;
    }
    // mObject is to the left
    else if (mObject.velocity.x < 0)
    {
        // mObject.x - objectsize.x / 2 = obstacle.x + obstaclesize.x / 2
        mObject.mRect.position.x = obstacle.position.x + obstacle.size.x / 2.f + mObject.mRect.size.x / 2.f;
    }

    // mObject is below
    if (mObject.velocity.y > 0)
    {
        mObject.mRect.position.y = obstacle.position.y - obstacle.size.y / 2.f - mObject.mRect.size.y / 2.f;
    }
    // mObject is above
    else if (mObject.velocity.y < 0)
    {
        // mObject.x - objectsize.x / 2 = obstacle.x + obstaclesize.x / 2
        mObject.mRect.position.y = obstacle.position.y + obstacle.size.y / 2.f + mObject.mRect.size.y / 2.f;
    }
    */

    if (mObject.velocity.x != 0)
    {
        int directionX = (mObject.velocity.x > 0) ? -1 : 1;
        mObject.mRect.position.x = obstacle.position.x + (obstacle.size.x / 2.f + mObject.mRect.size.x / 2.f) * directionX;
    }

    if (mObject.velocity.y != 0)
    {
        int directionY = (mObject.velocity.x > 0) ? 1 : -1;
        mObject.mRect.position.y = obstacle.position.y + (obstacle.size.y / 2.f + mObject.mRect.size.y / 2.f) * directionY;
    }
    
    // update velocity to 0
    mObject.velocity = Vec2d();
    
    // return remaining movement
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
    if (rightA <= leftB 
        || leftA >= rightB)
    {
        return false;
    }

    // if y bounds don't overlap
    if (bottomA >= topB
        || topA <= bottomB)
    {
        return false;
    }

    // do overlap in both dimensions
    return true;
}

//void Utils::moveElasticBounce(MoveableMRect& object, std::vector<MeshRect*> objectArr, double timeStep)
//{
//    object.mRect.position += object.velocity * timeStep;
//
//    for (auto it = objectArr.begin(); it != objectArr.end(); ++it)
//    {
//        if (checkCollision(object.mRect, **it))
//        {
//            Utils::calcElasticBounce(object, **it);
//
//            // TODO need to loop until all possible collisions are resolved
//        }
//    }
//}

void Utils::moveElasticBounce(MoveableMRect& object, Vec2d movement, std::vector<MeshRect*> objectArr)
{
    if (movement.x == 0.f && movement.y == 0.f)
    {
        return;
    }
    
    object.mRect.position += movement;

    for (auto it = objectArr.begin(); it != objectArr.end(); ++it)
    {
        if (checkCollision(object.mRect, **it))
        {
            movement = Utils::calcElasticBounce(object, **it);

            moveElasticBounce(object, movement, objectArr);
        }
    }
}

void Utils::moveStaticBounce(MoveableMRect& object, std::vector<MeshRect*> objectArr, double timeStep)
{
    object.mRect.position += object.velocity * timeStep;

    for (auto it = objectArr.begin(); it != objectArr.end(); ++it)
    {
        if (checkCollision(object.mRect, **it))
        {
            Utils::calcStaticBounce(object, **it);
        }
    }
}
