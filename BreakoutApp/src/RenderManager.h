#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameData.h"
#include "TextTexture.h"

// Renderer class abstracts SDL_Renderer
class RenderManager
{
public:

    // Fonts
    TTF_Font* gFontRegular;
    TTF_Font* gFontBoldLarge;

    // Colors
    const SDL_Color black = { 0,0,0,0 };
    const SDL_Color red = { 255,0,0,0 };
    const SDL_Color blue = { 0,0,255,0 };
    const SDL_Color green = { 0,125,0,0 };

    RenderManager();

    ~RenderManager() {};

    // unloads all textures and app context
    void close(AppContext& app, Textures& textures) const;

    // inits game renderer and game window
    bool init(AppContext& app) const;

    // loads fonts and returns true if sucessful, false otherwise
    bool loadFonts();

    // loads the image at specified path into given LTexture
    //bool loadFromFile(TextTexture& texture, std::string path, AppContext& app) const;

    // loads text string into a texture with the given color into given LTexture
    bool loadFromRenderedText(TextTexture& texture, TTF_Font* font, std::string textureText
        , SDL_Color textColor, AppContext& app) const;

    // loads game textures into Textures&
    bool loadTextures(AppContext& app, Textures& textures) const;

    void renderGame(const Textures& gTextures, GameState gState, GameObjects gObjects, AppContext& app);

    // render given texture at the given point, adapted to window size, optional clip for sprite sheet
    void renderTexture(const TextTexture& text, Vec2d position, AppContext& app
        , SDL_Rect* clip = nullptr) const;

    // render given rectangle while adapting it to window size
    void renderRect(const MeshRect& mRect, const SDL_Color& color, AppContext& app);

    // updates window size and scaling factor
    void updateWindowSize(Vec2i newSize, AppContext& app);
};
