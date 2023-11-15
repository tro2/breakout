#include "Physics.h"

#include <sstream>

#include "Logger.h"

bool Physics::checkCollision(const MeshRect& a, const MeshRect& b)
{
    // the sides to check collisions
    float leftA;
    float rightA;
    float topA;
    float bottomA;

    float leftB;
    float rightB;
    float topB;
    float bottomB;

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
    if (rightA <= leftB || leftA >= rightB)
    {
        return false;
    }

    // if y bounds don't overlap
    if (bottomA >= topB || topA <= bottomB)
    {
        return false;
    }

    // do overlap in both dimensions
    return true;
}

void Physics::moveElasticBounce(MoveableMRect& mObject, std::list<MeshRect>& obstacles, const std::forward_list<MeshRect*>& walls, const MoveableMRect& paddle, float timeStep)
{
    Vec2<float> movement = mObject.velocity * timeStep;
    
    while (movement.x != 0.f || movement.y != 0.f)
    {   
        movement = resolveElasticCollisions(mObject, movement, obstacles, walls, paddle, timeStep);
    }
}

void Physics::moveStaticBounce(MoveableMRect& mObject, const std::forward_list<MeshRect*>& obstacles, float timeStep)
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

Vec2<float> Physics::resolveElasticCollisions(MoveableMRect& mObject, Vec2<float> movement, std::list<MeshRect>& obstacles, const std::forward_list<MeshRect*>& walls, const MoveableMRect& paddle, float timeStep)
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
            Vec2<float> direction = mObject.velocity * (1 / mObject.maxVelocity);

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
    return Vec2<float>();
}

Vec2<float> Physics::resolveCollision(MoveableMRect& mObject, const MeshRect& obstacle, float timeStep, void (*velocityFunc)(MoveableMRect&, const MeshRect&))
{
    Vec2<float> distanceMoved;

    // opposite of mObject with length 0.1f
    Vec2<float> moveIncrement = mObject.velocity.unitVector() * -0.1f;

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
    distanceMoved = mObject.velocity.unitVector() * distanceMoved.magnitude();

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

    // TODO determine order of collision to accurately update velocity
    // only time both velocities should be updated would be on perfect corner collisions

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
    else
    {
        Logger::log(DEBUG, "could not determine collision");
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
    mObject.velocity = Vec2<float>();
}