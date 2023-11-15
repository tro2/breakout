#pragma once

#include <string>
#include <iostream>

#include <SDL.h>

#include "Vec2.h"

// Wrapper class for textures (just text for now)
class TextTexture
{
public:
    TextTexture();

    ~TextTexture();

    // dealloc texture
    void free();

    // get texture
    SDL_Texture* getMTexture() const { return mTexture; }

    // get dimensions
    int getWidth() const { return size.x; }
    int getHeight() const { return size.y; }
    Vec2<int> getSize() const { return size; }

    // sets texture pointer
    void setMTexture(SDL_Texture* texture) { mTexture = texture; }

    // sets dimensions
    void setWidth(int w) { size.x = w; }
    void setHeight(int h) { size.y = h; }
    void setSize(Vec2<int> size) { size.x = size.x; size.y = size.y; }

private:
    // the underlying texture
    SDL_Texture* mTexture;

    // Image dimensions in pixels
    Vec2<int> size;
};
