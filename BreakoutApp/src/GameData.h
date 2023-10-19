#pragma once

#include <SDL.h>

#include <array>

#include "TextTexture.h"

// INITIAL TYPES ================================

const Vec2d ARENA_SIZE = { 300.0f, 200.0f };

const float BALL_VELOCITY = 30.0f;
const float PADDLE_VELOCITY_TOTAL = 40.0f;
const Vec2d PADDLE_SIZE = Vec2d(50.0f, 5.0f);

// STRUCTS ======================================

struct AppContext {

    SDL_Window* gameWindow = nullptr;
    SDL_Renderer* gameRenderer = nullptr;

    Vec2i WINDOW_SIZE = { 720, 480 };
    float UNITS_PER_PIXEL = 2.4f;
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
    Paddle paddle;

    // ball
    Ball ball;
    
    // obstacles
    std::array<MeshRect, 10> obstacles{};

};
