#include "GameManager.h"

#include "Utils.h"

bool GameManager::loadObjects(GameObjects& gObjects)
{
	// game Arena
	gObjects.bottomWall 
        = MeshRect(Vec2d(0.0f, -ARENA_SIZE.y / 2.0f + WALL_WIDTH / 2.0f)
        , Vec2d(ARENA_SIZE.x, WALL_WIDTH));
	gObjects.topWall 
        = MeshRect(Vec2d(0.0f, ARENA_SIZE.y / 2.0f - WALL_WIDTH / 2.0f)
        , Vec2d(ARENA_SIZE.x, WALL_WIDTH));
	gObjects.leftWall 
        = MeshRect(Vec2d(-ARENA_SIZE.x / 2.0f + WALL_WIDTH / 2.0f, 0.0f)
        , Vec2d(WALL_WIDTH, ARENA_SIZE.y));
	gObjects.rightWall 
        = MeshRect(Vec2d(ARENA_SIZE.x / 2.0f - WALL_WIDTH / 2.0f, 0.0f)
        , Vec2d(WALL_WIDTH, ARENA_SIZE.y));

	// ball
	gObjects.ball.ballRect = MeshRect(Vec2d(50.0f, 50.0f), Vec2d(10.0f, 10.0f));
	gObjects.ball.velocity = Vec2d(0.0f, 0.0f);

	// paddle
	gObjects.paddle.paddleRect = { {0.0f, -100.0f},{50.0f, 5.0f} };
	gObjects.paddle.velocity = { 0.0f, 0.0f };

	return true;
}

void GameManager::update(GameObjects& gObjects, PaddleMove paddleMove)
{
    // move paddle and check collisions with walls

    // move ball and check collisions with
}

Vec2d GameManager::calcElasticBounce(MeshRect ball, MeshRect obstacle)
{
	return { 0.0f,0.0f };
}

bool GameManager::checkCollision(MeshRect a, MeshRect b)
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
    leftA = a.position.x;
    rightA = a.position.x + a.size.x;
    topA = a.position.y;
    bottomA = a.position.y + a.size.y;

    // Calculate the sides of rect B
    leftB = b.position.x;
    rightB = b.position.x + b.size.x;
    topB = b.position.y;
    bottomB = b.position.y + b.size.y;

    // if horizontal bounds do not overlap
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    // if vertical bounds do not overlap
    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    // both horizontal and vertical bounds overlap
    return true;
}