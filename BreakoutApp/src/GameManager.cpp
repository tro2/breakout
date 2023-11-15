#include "GameManager.h"

#include <vector>

#include "Physics.h"
#include "Utils.h"
#include "Vec2.h"

bool GameManager::loadObjects(GameObjects& gObjects)
{
    // game Arena
    gObjects.bottomWall = MeshRect(Vec2<float>(0.f, -ARENA_SIZE.y / 2.f + WALL_WIDTH / 2.f), Vec2<float>(ARENA_SIZE.x, WALL_WIDTH));
    gObjects.topWall = MeshRect(Vec2<float>(0.f, ARENA_SIZE.y / 2.f - WALL_WIDTH / 2.f), Vec2<float>(ARENA_SIZE.x, WALL_WIDTH));
    gObjects.leftWall = MeshRect(Vec2<float>(-ARENA_SIZE.x / 2.f + WALL_WIDTH / 2.f, 0.f), Vec2<float>(WALL_WIDTH, ARENA_SIZE.y));
    gObjects.rightWall = MeshRect(Vec2<float>(ARENA_SIZE.x / 2.f - WALL_WIDTH / 2.f, 0.f), Vec2<float>(WALL_WIDTH, ARENA_SIZE.y));

    // ball
    gObjects.ball.mRect = MeshRect(Vec2<float>(0.f, -ARENA_SIZE.y / 2.f + WALL_WIDTH + PADDLE_SIZE.y + BALL_SIZE.y / 2.f), BALL_SIZE);
    gObjects.ball.velocity = Vec2<float>(0.f, 0.f);
    gObjects.ball.maxVelocity = BALL_VELOCITY;

    // paddle
    gObjects.paddle.mRect = { {0.f, -ARENA_SIZE.y / 2.f + WALL_WIDTH + PADDLE_SIZE.y / 2.f}, PADDLE_SIZE};
    gObjects.paddle.velocity = { 0.f, 0.f };
    gObjects.paddle.maxVelocity = PADDLE_VELOCITY;

    // obstacles
    std::vector<Vec2<float>> posArr = Utils::generatePositions(INITIAL_TARGETS, OBSTACLE_SIZE, OBSTACLE_SECTION);
    gObjects.obstacles.clear();
    for (auto it = posArr.begin(); it != posArr.end(); ++it)
    {
        gObjects.obstacles.push_front(MeshRect(*it, OBSTACLE_SIZE));
    }

    // wall collision holder
    gObjects.wallObstacles.clear();
    gObjects.wallObstacles.push_front(&gObjects.leftWall);
    gObjects.wallObstacles.push_front(&gObjects.rightWall);
    gObjects.wallObstacles.push_front(&gObjects.topWall);

    // goal collision
    gObjects.goal = gObjects.bottomWall;
    gObjects.goal.position.y += WALL_WIDTH - 1;

    return true;
}

void GameManager::update(GameObjects& gObjects, GameState& gameState, PaddleMove& paddleMove, float timeStep)
{
    // PADDLE ===================================
    // move paddle and check collisions with walls
    gObjects.paddle.velocity.x = (static_cast<int>(paddleMove) - 1) * PADDLE_VELOCITY;
    Physics::moveStaticBounce(gObjects.paddle, gObjects.wallObstacles, timeStep);

    // reset paddleMove because otherwise paddle moves continously in direction last given
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
        // move ball and check collisions with GameObjects
        Physics::moveElasticBounce(gObjects.ball, gObjects.obstacles
            , gObjects.wallObstacles, gObjects.paddle, timeStep);

        if (gObjects.obstacles.size() == 0
            || Physics::checkCollision(gObjects.ball.mRect, gObjects.bottomWall))
        {
            // restart game
            gameState = GameState::READY;
            loadObjects(gObjects);
        }
    }
    
}
