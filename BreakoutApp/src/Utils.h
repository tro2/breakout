#pragma once

#include <vector>

#include <SDL.h>

#include "DataTypes.h"
#include "GameData.h"

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

    // PHYSICS ==================================
    
    // simulates elastic collision with a stationary obstacle
    // updates mObject velocity to velocity after collision
    // returns remaining movement
    Vec2d calcElasticBounce(MoveableMRect& mObject, const MeshRect& obstacle);

    // simulates inelastic collision with a stationary obstacle
    // updates mObject velocity to 0
    // returns remaining movement of 0
    Vec2d calcStaticBounce(MoveableMRect& mObject, const MeshRect& obstacle);

    // checks collisions between 2 rects
    bool checkCollision(const MeshRect& a, const MeshRect& b);

    // void moveElasticBounce(MoveableMRect& mObject, std::vector<MeshRect*> objectArr, double timeStep);
    void moveElasticBounce(MoveableMRect& mObject, Vec2d movement, std::vector<MeshRect*> objectArr);

    void moveStaticBounce(MoveableMRect& mObject, std::vector<MeshRect*> objectArr, double timeStep);

}
