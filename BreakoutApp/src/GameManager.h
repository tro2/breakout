#pragma once

#include "DataTypes.h"
#include "GameData.h"

class GameManager {
public:

	// initializes all game objects
	bool loadObjects(GameObjects& gObjects);

	// updates all game objects
	void update(GameObjects& gObjects, PaddleMove paddleMove);

private:

	// calculates final velocity of the ball after it bounces off given obstacle
	Vec2d calcElasticBounce(MeshRect ball, MeshRect obstacle);
	
	// checks collisions between 2 rects
	bool checkCollision(MeshRect a, MeshRect b);
};
