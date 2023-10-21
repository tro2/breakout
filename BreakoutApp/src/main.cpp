#include <iostream>
#include <sstream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "GameData.h"
#include "DataTypes.h"
#include "RenderManager.h"
#include "GameManager.h"
#include "Logger.h"

// FUNCTIONS ====================================

// Inits SDL
bool init();

// Cleans up SDL subsystems
void close();

int main(int, char**)
{
    // INIT =====================================
    
    // contains window and renderer data
    AppContext app;

    // contains all text textures
    Textures gameTextures;

    // contains fonts
    Fonts fonts;

    // contains all game MeshRects
    GameObjects gameObjects;

    // handles loading and rendering assets
    RenderManager renderManager;

    // handles game object updates
    GameManager gameManager;
    
    // Start SDL
    if (!init())
    {
        Logger::log(LogLevel::ERROR, "Failed to init SDL!");
        return -1;
    }

    // Create renderer and Window
    if (!renderManager.init(app))
    {
        Logger::log(LogLevel::ERROR, "Failed to load app context!");
        return -1;
    }

    // Load fonts
    if (!renderManager.loadFonts(fonts))
    {
        Logger::log(LogLevel::ERROR, "Failed to load fonts!");
        return -1;
    }

    // load initial textures
    if (!renderManager.loadTextures(app, gameTextures, fonts))
    {
        Logger::log(LogLevel::ERROR, "Failed to load textures!");
        return -1;
    }

    // load gameObjects
    if (!gameManager.loadObjects(gameObjects))
    {
        Logger::log(LogLevel::ERROR, "Failed to load game objects!");
        return -1;
    }

    // FLAGS ====================================

    bool quit = false;
    GameState currentState = GameState::READY;

    // GAME LOOP ================================

    // event storage
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                renderManager.updateWindowSize(Vec2i(e.window.data1, e.window.data2), app);
            }
        }

        // INPUT ================================

        // update gameState
        PaddleMove paddleMove = PaddleMove::STILL;

        // UPDATE OBJECTS =======================
        if (currentState == GameState::IN_GAME) // do I need this check? is this branching
        {
            gameManager.update(gameObjects, paddleMove);
        }

        // RENDER ===============================
        renderManager.renderGame(gameTextures, currentState, gameObjects, app);

    }

    // CLOSE ====================================

    close();
    
    return 0;
}

bool init()
{
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::string log = "SDL could not be initialized! SDL Error: ";
        Logger::log(LogLevel::ERROR, log + SDL_GetError());
        return false;
    }

    //// init png loading
    //int imgFlags = IMG_INIT_PNG;
    //if (!(IMG_Init(imgFlags) & imgFlags))
    //{
    //    std::string log = "SDL_image could not be created! SDL_image Error: ";
    //    Logger::log(LogLevel::ERROR, log + IMG_GetError());
    //    return false;
    //}

    // init SDL_ttf
    if (TTF_Init() == -1)
    {
        std::string log = "SDL_ttf could not initialize! SDL_ttf Error: ";
        Logger::log(LogLevel::ERROR, log + TTF_GetError());
        return false;
    }

    return true;
}

void close()
{
    // Quit SDL subsystem
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
