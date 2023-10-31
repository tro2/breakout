#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <forward_list>
#include <list>

#include "MeshRect.h"
#include "TextTexture.h"
#include "Vec2.h"

// INITIAL TYPES ================================

const Vec2d ARENA_SIZE = { 300.f, 200.f };
const double WALL_WIDTH = 5.f;

const Vec2d BALL_SIZE = Vec2d(5.f, 5.f);
const double BALL_VELOCITY = 80.f;

const Vec2d PADDLE_SIZE = Vec2d(50.f, 5.f);
const double PADDLE_VELOCITY = 100.f;

const int INITIAL_TARGETS = 10;
const Vec2d OBSTACLE_SIZE = Vec2d(30.f, 20.f);
const Vec2d OBSTACLE_SECTION = Vec2d(250.f, 100.f);


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

    Vec2i WINDOW_SIZE = { 720, 480 };
    double PIXELS_PER_UNIT = WINDOW_SIZE.x/ARENA_SIZE.x;
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
