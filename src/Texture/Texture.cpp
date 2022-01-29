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
    mLoadedFont = NULL;
}




SDL_Texture* Texture::loadTexture(TextFormat& formatInfo, std::string& displayText)
{
    free();
    SDL_Texture* newTexture = NULL;

    if (mLoadedFont == NULL)
    {
        	std::string errormsg = "Font could not be loaded";
			SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, errormsg.c_str());
            return NULL;
    }
    else
    {
        // render text surface
        SDL_Surface* txtSurface = TTF_RenderText_Solid(mLoadedFont, displayText.c_str(),
        formatInfo.color );

        if (txtSurface == NULL)
        {
            std::string errormsg = "Font could not be loaded";
            SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, errormsg.c_str());
            newTexture = NULL;
        }
        else
        {
            //Create texture from surface pixels
            newTexture = SDL_CreateTextureFromSurface(Global::appRenderer, txtSurface);

            if (txtSurface == NULL)
            {
                std::string errormsg = "Font could not be loaded";
                SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, errormsg.c_str());
                newTexture = NULL;
            }
            else{
                // get dimensions
                mWidth = txtSurface->w;
                mHeight = txtSurface->h;
            }
           
        }
    
            SDL_FreeSurface(txtSurface);
    }

    return newTexture;

}
	
SDL_Texture* Texture::loadTexture(std::string& imagePath)
{
    free();
    
    SDL_Texture* newTexture = NULL;

    // load image #TODO: add init of img engine!!
    SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());

    if(loadedSurface == NULL)
    {
        std::string errormsg = "Texture could not be created.";
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, errormsg.c_str());
        return NULL;

    }
    // Create new texture from surface pixels 
    newTexture = SDL_CreateTextureFromSurface(Global::appRenderer, loadedSurface);
    if(newTexture == NULL)
    {
            std::string errormsg = "Texture could not be created.";
            SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, errormsg.c_str());
            return NULL;

    }
    
    // free old loaded surface
    SDL_FreeSurface(loadedSurface);

    return newTexture;

}

TTF_Font* Texture::loadFont()
{
    TTF_Font* font = NULL;

	font = TTF_OpenFont(mFormat.fontPath.c_str(), mFormat.fontSize);
	if( font == NULL || TTF_WasInit() == 0 ) // TODO: seperate thesse conditions
	{
		// could not load font
        printf( "Font could not be loaded! Error: %s\n", TTF_GetError() );
        return NULL;

	}

    return font;
}

void Texture::free()
{
    //get rid of loaded texture and set pointer to NULL
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = mHeight = 0;
    }
}
