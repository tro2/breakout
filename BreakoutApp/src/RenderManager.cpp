#include "RenderManager.h"

#include <iostream>

#include <SDL_image.h>

#include "Utils.h"
#include "GameData.h"

RenderManager::RenderManager()
{
    // Fonts
    TTF_Font* gFontRegular = nullptr;
    TTF_Font* gFontBoldLarge = nullptr;

}

void RenderManager::close(AppContext& appContext, Textures& textures) const
{
    // Deallocate textures
    textures.spacebarStartText.free();
    textures.victoryText.free();
    textures.restartText.free();

    // Dealloc Fonts
    TTF_CloseFont(gFontRegular);
    TTF_CloseFont(gFontBoldLarge);

    SDL_DestroyRenderer(appContext.gameRenderer);
    appContext.gameRenderer = nullptr;

    // Destroy window
    SDL_DestroyWindow(appContext.gameWindow);
    appContext.gameWindow = nullptr;
}

bool RenderManager::init(AppContext& appContext) const
{
    // create the window
    appContext.gameWindow = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED
        , SDL_WINDOWPOS_UNDEFINED, appContext.WINDOW_SIZE.x, appContext.WINDOW_SIZE.y
        , SDL_WINDOW_SHOWN);
    if (appContext.gameWindow == nullptr)
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // create renderer for the main window
    appContext.gameRenderer = SDL_CreateRenderer(appContext.gameWindow, -1
        , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (appContext.gameRenderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

bool RenderManager::loadFonts()
{
    // load flag
    bool success = true;

    gFontRegular = TTF_OpenFont("arial.ttf", 14);
    if (gFontRegular == nullptr)
    {
        printf("Unable to load regular font! TTF Error: %s\n", TTF_GetError());
        success = false;
    }

    gFontBoldLarge = TTF_OpenFont("arial.ttf", 20);
    if (gFontBoldLarge == nullptr)
    {
        printf("Unable to load large bold font! TTF Error: %s\n", TTF_GetError());
        success = false;
    }

    // set font to bold
    TTF_SetFontStyle(gFontBoldLarge, TTF_STYLE_BOLD);

    return success;
}

//bool RenderManager::loadFromFile(TextTexture& lTexture, std::string path, AppContext& appContext) const
//{
//    // remove possible preexisting texture
//    lTexture.free();
//
//    // first create a surface, then convert
//    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//    if (loadedSurface == nullptr)
//    {
//        std::cout << "Unable to load iamge " << path << "! SDL_image error: " << IMG_GetError()
//            << std::endl;
//    }
//    else
//    {
//        // color key the image
//        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
//
//        // convert surface to texture
//        lTexture.setMTexture(SDL_CreateTextureFromSurface(appContext.gameRenderer, loadedSurface));
//        if (lTexture.getMTexture() == nullptr)
//        {
//            std::cout << "Unable to create texture from " << path << "! SDL Error: "
//                << SDL_GetError() << std::endl;
//        }
//        else
//        {
//            lTexture.setWidth(static_cast<double>(loadedSurface->w));
//            lTexture.setHeight(static_cast<double>(loadedSurface->h));
//        }
//
//        // get rid of old surface
//        SDL_FreeSurface(loadedSurface);
//    }
//
//    // return success
//    return lTexture.getMTexture() != nullptr;
//}

bool RenderManager::loadFromRenderedText(TextTexture& lTexture, TTF_Font* font, std::string textureText
    , SDL_Color textColor, AppContext& appContext) const
{
    // remove possible preexisting texture
    lTexture.free();

    // render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // convert surface to texture
        lTexture.setMTexture(SDL_CreateTextureFromSurface(appContext.gameRenderer, textSurface));
        if (lTexture.getMTexture() == nullptr)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            lTexture.setWidth(textSurface->w);
            lTexture.setHeight(textSurface->h);
        }

        // get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    // return success
    return lTexture.getMTexture() != nullptr;
}

bool RenderManager::loadTextures(AppContext& appContext, Textures& textures) const
{
    // load flag
    bool success = true;

    // text textures
    if (!loadFromRenderedText(textures.spacebarStartText, gFontRegular
        , "Press Spacebar to start", black, appContext))
    {
        printf("Unable to load test text!\n");
        success = false;
    }

    if (!loadFromRenderedText(textures.victoryText, gFontRegular, "Victory!", black
        , appContext))
    {
        printf("Unable to load victory text!\n");
        success = false;
    }

    if (!loadFromRenderedText(textures.restartText, gFontRegular, "Press 'R' to restart..."
        , black, appContext))
    {
        printf("Unable to load restart text!\n");
        success = false;
    }

    return success;
}

void RenderManager::renderGame(const Textures& gTextures, GameState gState, GameObjects gObjects, AppContext& app)
{
    // Clear screen and prep for render pass
    SDL_RenderClear(app.gameRenderer);
    SDL_SetRenderDrawColor(app.gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // render game objects
    renderRect(gObjects.bottomWall, green, app);
    renderRect(gObjects.topWall, green, app);
    renderRect(gObjects.leftWall, green, app);
    renderRect(gObjects.rightWall, green, app);

    renderRect(gObjects.paddle.paddleRect, blue, app);

    renderRect(gObjects.ball.ballRect, black, app);

    // render text
    renderTexture(gTextures.victoryText, { 0.0f, -10.0f }, app);

    SDL_SetRenderDrawColor(app.gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Update screen
    SDL_RenderPresent(app.gameRenderer);
}

void RenderManager::renderTexture(const TextTexture& lTexture, Vec2d position, AppContext& app
    , SDL_Rect* clip) const
{
    // define rendering space and render

    // position is given relative to world origin in center and position marking center of mesh
    // size of texture is pixels
    Vec2i posI = Utils::convVec(Utils::scaleVecD(position, app.UNITS_PER_PIXEL));
    Vec2i sizeI = lTexture.getSize();

    // conv pos to rect origin at top left
    posI.x -= sizeI.x / 2;
    posI.y += sizeI.y / 2;

    // conv pos to relative to top left
    posI.x = app.WINDOW_SIZE.x / 2 + posI.x;
    posI.y = app.WINDOW_SIZE.y / 2 - posI.y;

    SDL_Rect renderQuad = { posI.x, posI.y, sizeI.x, sizeI.y };

    // set clip rendering rect
    if (clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(app.gameRenderer, lTexture.getMTexture(), clip, &renderQuad);
}

void RenderManager::renderRect(const MeshRect& mRect, const SDL_Color& color, AppContext& app)
{
    // position is given relative to world origin in center and position marking center of mesh
    Vec2i posI = Utils::convVec(Utils::scaleVecD(mRect.position, app.UNITS_PER_PIXEL));
    Vec2i sizeI = Utils::convVec(Utils::scaleVecD(mRect.size, app.UNITS_PER_PIXEL));

    // conv pos to rect origin at top left
    posI.x -= sizeI.x / 2;
    posI.y += sizeI.y / 2;

    // conv pos to relative to top left
    posI.x = app.WINDOW_SIZE.x / 2 + posI.x;
    posI.y = app.WINDOW_SIZE.y / 2 - posI.y;
    
    SDL_Rect renderQuad = { posI.x, posI.y, sizeI.x, sizeI.y };
    
    SDL_SetRenderDrawColor(app.gameRenderer, color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(app.gameRenderer, &renderQuad);
}
