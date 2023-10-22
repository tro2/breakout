#include "GameManager.h"

#include "Utils.h"

bool GameManager::loadObjects(GameObjects& gObjects)
{
	// game Arena
	gObjects.bottomWall 
        = MeshRect(Vec2d(0.f, -ARENA_SIZE.y / 2.f + WALL_WIDTH / 2.f)
        , Vec2d(ARENA_SIZE.x, WALL_WIDTH));
	gObjects.topWall 
        = MeshRect(Vec2d(0.f, ARENA_SIZE.y / 2.f - WALL_WIDTH / 2.f)
        , Vec2d(ARENA_SIZE.x, WALL_WIDTH));
	gObjects.leftWall 
        = MeshRect(Vec2d(-ARENA_SIZE.x / 2.f + WALL_WIDTH / 2.f, 0.f)
        , Vec2d(WALL_WIDTH, ARENA_SIZE.y));
	gObjects.rightWall 
        = MeshRect(Vec2d(ARENA_SIZE.x / 2.f - WALL_WIDTH / 2.f, 0.f)
        , Vec2d(WALL_WIDTH, ARENA_SIZE.y));

	// ball
    gObjects.ball.mRect = MeshRect(
          Vec2d(0.f, -ARENA_SIZE.y / 2.f + WALL_WIDTH + PADDLE_SIZE.y + BALL_SIZE.y / 2.f)
        , BALL_SIZE);
	gObjects.ball.velocity = Vec2d(0.f, 0.f);

	// paddle
    gObjects.paddle.mRect = { {ARENA_SIZE.x / 2.f, -ARENA_SIZE.y / 2.f + WALL_WIDTH + PADDLE_SIZE.y / 2.f}, PADDLE_SIZE};
    //gObjects.paddle.mRect = { {0.f, -ARENA_SIZE.y / 2.f + WALL_WIDTH + PADDLE_SIZE.y / 2.f}, PADDLE_SIZE};
	gObjects.paddle.velocity = { 0.f, 0.f };

	return true;
}

void GameManager::update(GameObjects& gObjects, PaddleMove paddleMove)
{
    // move paddle and check collisions with walls

    // move ball and check collisions with
}

Vec2d GameManager::calcElasticBounce(MeshRect ball, MeshRect obstacle)
{
	return { 0.f,0.f };
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