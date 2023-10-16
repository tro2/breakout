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

// FUNCTIONS ====================================

// Inits SDL
bool init();

// Cleans up SDL subsystems
void close();

int main(int, char**)
{
    // INIT =====================================
    
    AppContext app;
    RenderManager renderManager;
    Textures gameTextures;
    
    // Start SDL
    if (!init())
    {
        std::cout << "Failed to init SDL!" << std::endl;
        return -1;
    }

    // Create renderer and Window
    if (!renderManager.init(app))
    {
        std::cout << "Failed to load app context!" << std::endl;
        return -1;
    }

    // Load fonts
    if (!renderManager.loadFonts())
    {
        std::cout << "Failed to load fonts!" << std::endl;
        return -1;
    }

    // load initial textures
    if (!renderManager.loadTextures(app, gameTextures))
    {
        std::cout << "Failed to load textures!" << std::endl;
        return -1;
    }
    
    // FLAGS ====================================

    bool quit = false;

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
        }

        // INPUT ================================

        // UPDATE OBJECTS =======================

        // RENDER ===============================

        // Clear screen and prep for render pass
        SDL_RenderClear(app.gameRenderer);
        SDL_SetRenderDrawColor(app.gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        renderManager.renderRect({{ 0.0f,0.0f },{ 100.0f,100.0f, }}, renderManager.red, app);
        renderManager.renderTexture(gameTextures.victoryText, { 0.0f, 0.0f }, app);

        SDL_SetRenderDrawColor(app.gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Update screen
        SDL_RenderPresent(app.gameRenderer);

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
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError()
            << std::endl;
        return false;
    }

    //// init png loading
    //int imgFlags = IMG_INIT_PNG;
    //if (!(IMG_Init(imgFlags) & imgFlags))
    //{
    //    std::cout << "SDL_image could not be created! SDL_image Error: " << IMG_GetError()
    //        << std::endl;
    //    return false;
    //}

    // init SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError()
            << std::endl;
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
