#include "TextTexture.h"

#include <SDL_image.h>

TextTexture::TextTexture()
{
    mTexture = NULL;

    size = { 0,0 };
}

TextTexture::~TextTexture()
{
    // dealloc
    free();
}

void TextTexture::free()
{
    // if texture exists
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        size = { 0,0 };
    }
}
