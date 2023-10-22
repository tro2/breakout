#include "GameManager.h"

#include <vector>

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
    gObjects.paddle.mRect = { {0.f, -ARENA_SIZE.y / 2.f + WALL_WIDTH + PADDLE_SIZE.y / 2.f}, PADDLE_SIZE};
    gObjects.paddle.velocity = { 0.f, 0.f };

    return true;
}

void GameManager::update(GameObjects& gObjects, GameState& gameState, PaddleMove& paddleMove, double timeStep)
{
    // PADDLE ===================================
    // move paddle and check collisions with walls
    gObjects.paddle.velocity.x = (paddleMove - 1) * PADDLE_VELOCITY;
    std::vector<MeshRect*> vec = { &gObjects.leftWall, &gObjects.rightWall };
    Utils::moveStaticBounce(gObjects.paddle, vec, timeStep);
    // reset paddleMove because otherwise paddle moves continously in direction last given
    // 
    paddleMove = PaddleMove::STILL;

    // BALL =====================================
    // move ball around for launching
    if (gameState == GameState::READY)
    {
        // move ball with paddle
        gObjects.ball.mRect.position.x = gObjects.paddle.mRect.position.x;
    }
    else if (gameState == GameState::IN_GAME)
    {
        vec.push_back(&gObjects.topWall);
        vec.push_back(&gObjects.bottomWall);
        vec.push_back(&gObjects.paddle.mRect);
        // move ball and check collisions with GameObjects
        Utils::moveElasticBounce(gObjects.ball, gObjects.ball.velocity * timeStep, vec);
    }
    
}
