#pragma once

#include <list>
#include <forward_list>

#include "MeshRect.h"
#include "Vec2.h"

namespace Physics
{

    // checks collisions between 2 rects
    bool checkCollision(const MeshRect& a, const MeshRect& b);

    // moves ball and checks against all objects, updating game state as necessary
    void moveElasticBounce(MoveableMRect& mObject, std::list<MeshRect>& obstacles
        , const std::forward_list<MeshRect*>& walls, const MoveableMRect& paddle, float timeStep);

    // moves paddle and checks against walls
    void moveStaticBounce(MoveableMRect& mObject, const std::forward_list<MeshRect*>& obstacles, float timeStep);

    // assuming non-zero movement, checks and resolves collisions of mObject
    // returns movement remaining after collision
    Vec2<float> resolveElasticCollisions(MoveableMRect& mObject, Vec2<float> movement, std::list<MeshRect>& obstacles, const std::forward_list<MeshRect*>& walls, const MoveableMRect& paddle, float timeStep);

    // assuming mObject and obstacle are colliding
    // moves mObject out of obstacle
    // updates velocity based on func
    // returns the distance moved
    Vec2<float> resolveCollision(MoveableMRect& mObject, const MeshRect& obstacle, float timeStep, void (*velocityFunc)(MoveableMRect&, const MeshRect&));

    // assuming mObject and obstacle are colliding
    // updates mObject velocity for elastic collision between stationary and moving object
    void resolveElasticCollisionVelocity(MoveableMRect& mObject, const MeshRect& obstacle);

    // assuming mObject and paddle are colliding
    // updates mObject velocity for specific paddle velocity
    void resolvePaddleCollisionVelocity(MoveableMRect& ball, const MeshRect& paddle);

    // assuming collision
    // updates mObject velocity to 0
    void resolveStaticCollisionVelocity(MoveableMRect& mObject, const MeshRect& obstacle);
}
