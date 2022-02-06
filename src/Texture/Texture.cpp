#include "Texture.hpp"  
	
Texture::Texture(int x, int y)
{
    mPosX = x;
    mPosY = y;
    

}

Texture::Texture(int x, int y, TTF_Font* font, std::string& displayText)
{
    mPosX = x;
    mPosY = y;
    mLoadedFont = font;



    // mFormat = formatInfo;
    // mLoadedFont = loadFont();
    mTexture = loadTexture(font,displayText);

}

Texture::Texture(int x, int y, std::string& imagePath)
{
    
    mPosX = x;
    mPosY = y;
    
    mTexture = loadTexture(imagePath);
    
}

Texture::~Texture()
{
    
	free();
    // will be handled by owning object
    // TTF_CloseFont(mLoadedFont);
    mLoadedFont = NULL;
}




SDL_Texture* Texture::loadTexture(TTF_Font* font, std::string& displayText)
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
        mFormat.color );

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

            if (newTexture == NULL)
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
        newTexture = NULL;

    }
    else
    {
        // Create new texture from surface pixels 
        newTexture = SDL_CreateTextureFromSurface(Global::appRenderer, loadedSurface);
        if(newTexture == NULL)
        {
                std::string errormsg = "Texture could not be created.";
                SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, errormsg.c_str());
                newTexture = NULL;

        }
        else
        {
            // get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }


    // free old loaded surface
    SDL_FreeSurface(loadedSurface);
    }
    

    return newTexture;

}


void Texture::render()
{
    // set rendering space and draw
    SDL_Rect renderRect = {mPosX,mPosY,mWidth,mHeight};

    SDL_RenderCopy(Global::appRenderer, mTexture, NULL, &renderRect);
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

void Texture::setTexture(TTF_Font* font, std::string& displayText)
{

    mTexture = loadTexture(font, displayText);

}
void Texture::setTexture(std::string& imagePath)
{

    mTexture = loadTexture(imagePath);
}

bool Texture::checkTexture()
{
    return mTexture != NULL;
}

int Texture::getWidth(){
    return mWidth;
}

int Texture::getHeight(){
    return mHeight;
}

TTF_Font* Texture::getFont(){
    return mLoadedFont;
}
