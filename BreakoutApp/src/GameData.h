#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <forward_list>
#include <list>

#include "MeshRect.h"
#include "TextTexture.h"
#include "Vec2.h"

// INITIAL TYPES ================================

const Vec2<float> ARENA_SIZE = { 300.f, 200.f };
const float WALL_WIDTH = 5.f;

const Vec2<float> BALL_SIZE = Vec2<float>(5.f, 5.f);
const float BALL_VELOCITY = 80.f;
const float SPEED_INCREMENT = 5.f;

const Vec2<float> PADDLE_SIZE = Vec2<float>(50.f, 5.f);
const float PADDLE_VELOCITY = 150.f;

const int INITIAL_TARGETS = 30;
const Vec2<float> OBSTACLE_SIZE = Vec2<float>(25.f, 15.f);
const Vec2<float> OBSTACLE_SECTION = Vec2<float>(250.f, 100.f);


// ENUMS ========================================

enum GameState
{
    READY,
    IN_GAME,
    VICTORY,
};

enum PaddleMove
{
    LEFT,
    STILL,
    RIGHT
};

// STRUCTS ======================================

struct AppContext {

    SDL_Window* gameWindow = nullptr;
    SDL_Renderer* gameRenderer = nullptr;

    Vec2<int> WINDOW_SIZE = { 720, 480 };
    float PIXELS_PER_UNIT = WINDOW_SIZE.x/ARENA_SIZE.x;
};

struct Textures {

    // text textures
    TextTexture spacebarStartText;
    TextTexture victoryText;
    TextTexture restartText;
};

struct GameObjects {

    // arena
    MeshRect topWall;
    MeshRect bottomWall;
    MeshRect leftWall;
    MeshRect rightWall;

    // paddle
    MoveableMRect paddle;

    // ball
    MoveableMRect ball;
    
    // obstacles
    std::list<MeshRect> obstacles;

    // for collision purposes
    std::forward_list<MeshRect*> wallObstacles;
    MeshRect goal;
};

struct Fonts {

    TTF_Font* gFontRegular;
    TTF_Font* gFontBoldLarge;
};
