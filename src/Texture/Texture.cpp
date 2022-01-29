#include "Texture.hpp"  
	
Texture::Texture()
{
	
}

Texture::Texture(TextFormat& formatInfo, std::string& displayText)
{
    mFormat = formatInfo;
    mLoadedFont = loadFont();
    mTexture = loadTexture(formatInfo,displayText);

}

Texture::Texture(std::string& imagePath)
{
    
    mTexture = loadTexture(imagePath);
    
}

Texture::~Texture()
{
	free();
}

SDL_ Texture* Texture::loadTexture(TextFormat& formatInfo, std::string& displayText)
{
    return NULL;
}
	
SDL_ Texture* Texture::loadTexture(std::string& imagePath)
{
    SDL_Texture* newTexture = NULL;

    // load image #TODO: add init of img engine!!
    SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());

    if(loadedSurface == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", imagePath.c_str(), IMG_GetError() );
    }

    // Create new texture from surface pixels 
    newTexture = SDL_CreateTextureFromSurface(Global::appRenderer, loadedSurface);
    if(newTexture == NULL)
    {
        printf( "Unable to load texture %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError() );

    }
    
    // free old loaded surface
    SDL_FreeSurface(loadedSurface);

    return newTexture;

}
