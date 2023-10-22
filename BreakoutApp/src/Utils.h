#pragma once

#include <vector>

//#include <SDL.h>

#include "DataTypes.h"

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

    //SDL_Rect convMeshRect(const MeshRect& mRect);

    // TODO make this into a class function
    Vec2d scaleVecD(const Vec2d& vecD, double scalar);
    // TODO make this into a class function
    Vec2i scaleVecI(const Vec2i& vecI, float scalar);


    // PHYSICS ==================================
    
    // calculates final remaining move of the ball after it bounces off given obstacle
    // updates ball velocity
    Vec2d calcElasticBounce(MoveableMRect& ball, const MeshRect& obstacle);

    // updates paddle velocity after collision with wall, returns Vec2d of 0,0
    Vec2d calcStaticBounce(MoveableMRect& paddle, const MeshRect& obstacle);

    // checks collisions between 2 rects
    bool checkCollision(const MeshRect& a, const MeshRect& b);

    void moveElasticBounce(MoveableMRect& object, std::vector<MeshRect*> objectArr);

    void moveStaticBounce(MoveableMRect& object, std::vector<MeshRect*> objectArr);

}
