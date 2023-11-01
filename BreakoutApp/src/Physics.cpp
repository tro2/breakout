#include "Physics.h"

#include <sstream>

#include "Logger.h"

bool Physics::checkCollision(const MeshRect& a, const MeshRect& b)
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

void Physics::moveElasticBounce(MoveableMRect& mObject, std::list<MeshRect>& obstacles
    , const std::forward_list<MeshRect*>& walls, const MoveableMRect& paddle, double timeStep)
{
    Vec2d movement = mObject.velocity * timeStep;
    
    while (movement.x != 0.f || movement.y != 0.f)
    {   
        movement = resolveElasticCollisions(mObject, movement, obstacles, walls, paddle, timeStep);
    }
}

void Physics::moveStaticBounce(MoveableMRect& mObject, const std::forward_list<MeshRect*>& obstacles, double timeStep)
{
    mObject.mRect.position += mObject.velocity * timeStep;

    for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
    {
        if (checkCollision(mObject.mRect, **it))
        {
            Physics::resolveCollision(mObject, **it, timeStep, resolveStaticCollisionVelocity);
        }
    }
}

Vec2d Physics::resolveElasticCollisions(MoveableMRect& mObject, Vec2d movement, std::list<MeshRect>& obstacles
    , const std::forward_list<MeshRect*>& walls, const MoveableMRect& paddle, double timeStep)
{
     mObject.mRect.position += movement;

    // check paddle
    if (checkCollision(mObject.mRect, paddle.mRect))
    {
        return Physics::resolveCollision(mObject, paddle.mRect, timeStep, resolvePaddleCollisionVelocity);
    }

    // check deletable objects for collisions
    for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
    {
        if (checkCollision(mObject.mRect, *it))
        {   
            movement = Physics::resolveCollision(mObject, *it, timeStep, resolveElasticCollisionVelocity);

            // erase obstacle
            it = obstacles.erase(it);

            // increase velocity
            Vec2d direction = mObject.velocity * (1 / mObject.maxVelocity);

            mObject.maxVelocity += 5;
            mObject.velocity = direction * mObject.maxVelocity;

            // add one to score

            return movement;
        }
    }

    // check walls for collisions
    for (auto it = walls.begin(); it != walls.end(); ++it)
    {
        if (checkCollision(mObject.mRect, **it))
        {
            return Physics::resolveCollision(mObject, **it, timeStep, resolveElasticCollisionVelocity);
        }
    }

    // return 0 if no collisions detected
    return Vec2d();
}

Vec2d Physics::resolveCollision(MoveableMRect& mObject, const MeshRect& obstacle, double timeStep
    , void (*velocityFunc)(MoveableMRect&, const MeshRect&))
{
    Vec2d distanceMoved;

    // opposite of mObject with length 0.1f
    Vec2d moveIncrement = mObject.velocity * -(1/mObject.maxVelocity) * 0.1f;

    // update mObject velocity
    velocityFunc(mObject, obstacle);

    do
    {
        // move mObject back a bit
        mObject.mRect.position += moveIncrement;

        // record how much you moved back
        distanceMoved += moveIncrement;
    } while (checkCollision(mObject.mRect, obstacle));
    
    // reorient movement vector in the direction of the object new velocity
    // unit vector pointed in direction of  object's new velocity
    Vec2d direction = mObject.velocity * (1 / mObject.maxVelocity);

    distanceMoved = direction * distanceMoved.magnitude();

    return distanceMoved;
}

void Physics::resolveElasticCollisionVelocity(MoveableMRect& mObject, const MeshRect& obstacle)
{
    // Calculate the sides of rect A
    double leftA = mObject.mRect.position.x - mObject.mRect.size.x / 2.f;
    double rightA = mObject.mRect.position.x + mObject.mRect.size.x / 2.f;
    double topA = mObject.mRect.position.y + mObject.mRect.size.y / 2.f;
    double bottomA = mObject.mRect.position.y - mObject.mRect.size.y / 2.f;

    // Calculate the sides of rect B
    double leftB = obstacle.position.x - obstacle.size.x / 2.f;
    double rightB = obstacle.position.x + obstacle.size.x / 2.f;
    double topB = obstacle.position.y + obstacle.size.y / 2.f;
    double bottomB = obstacle.position.y - obstacle.size.y / 2.f;

    // TODO fix bug with collisions on corners of rectangles

    // determine which side was hit using velocity and position of rectangles
    if (mObject.velocity.x > 0)
    {
        // right side
        if (rightA >= leftB && leftA <= leftB)
        {
            mObject.velocity.x *= -1;

            //Logger::log(DEBUG, "collided from left");
        }
    }
    else if (mObject.velocity.x < 0)
    {
        // left side
        if (leftA <= rightB && rightA >= rightB)
        {
            mObject.velocity.x *= -1;

            //Logger::log(DEBUG, "collided from right");
        }
    }
    
    if (mObject.velocity.y > 0)
    {
        // top side
        if (topA >= bottomB && bottomA <= bottomB)
        {
            mObject.velocity.y *= -1;

            //Logger::log(DEBUG, "collided from the bottom");
        }
    }
    else if (mObject.velocity.y < 0)
    {
        // bottom side
        if (bottomA <= topB && topA >= topB)
        {
            mObject.velocity.y *= -1;

            //Logger::log(DEBUG, "collided from the top");
        }
    }
    else
    {
        Logger::log(DEBUG, "could not determine collision");
    }
}

void Physics::resolvePaddleCollisionVelocity(MoveableMRect& ball, const MeshRect& paddle)
{
    // theta = offset from paddle center * scaling factor (scales 0 - pSize/2 up to 0-45)
    double launchAngle = (ball.mRect.position.x - paddle.position.x) * -45 / paddle.size.x * 2;
    launchAngle += 90;

    // convert to radians
    launchAngle *= 3.1415926f / 180;

    ball.velocity.x = ball.maxVelocity * cos(launchAngle);
    ball.velocity.y = ball.maxVelocity * sin(launchAngle);
}

void Physics::resolveStaticCollisionVelocity(MoveableMRect& mObject, const MeshRect& obstacle)
{
    // set mObject velocity to 0
    mObject.velocity = Vec2d();
}