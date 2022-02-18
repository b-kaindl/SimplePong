#include "PTexture.hpp"  
	
PTexture::PTexture()
{
	mWidth = mHeight = 0;
    mTexture = NULL;
}
	
PTexture::~PTexture()
{
	// Deallocate
    free();
}

bool PTexture::loadFromFile( std::string filePath )
{
    // idea - add default color for color keying analogously to Lazyfoo
    free();

    // final texture
    SDL_Texture* newTexture = NULL;

    // load image at path
    SDL_Surface* loadedSurface = IMG_Load( filePath.c_str());

    if( loadedSurface == NULL )
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to load image %s! SDL_image Error: %s\n", 
        filePath.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( Global::appRenderer, loadedSurface );
        if (newTexture == NULL)
        {
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to create texture from %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError() );

        }
        else
        {
            // adjust dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // lose loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    // return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void PTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = mHeight = 0;
    }
}

void PTexture::render(int x, int y)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( Global::appRenderer, mTexture, NULL, &renderQuad );
}

int PTexture::getHeight()
{
    return mHeight;
}

int PTexture::getWidth()
{
    return mWidth;
}