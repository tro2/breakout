#pragma once

#include <SDL.h>

#include "TextTexture.h"

// INITIAL TYPES ================================

const Vec2d ARENA_SIZE = { 300.0f, 200.0f };

// STRUCTS ======================================

struct AppContext {

    SDL_Window* gameWindow = nullptr;
    SDL_Renderer* gameRenderer = nullptr;

    Vec2i WINDOW_SIZE = { 720, 480 };
    float UNITS_PER_PIXEL = 2.4f;
};

struct GameObjects {



};

struct Textures {

    // text textures
    TextTexture spacebarStartText;
    TextTexture victoryText;
    TextTexture restartText;
    TextTexture scoreText;

};
