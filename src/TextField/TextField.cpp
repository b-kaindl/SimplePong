#include "TextField.hpp"  
	
TextField::TextField(SDL_Rect& fieldRect, TextFormat& fieldFormat, std::string displayText)
{
	// load format
	mFormat = fieldFormat;
	mViewport = fieldRect;
	mDisplayText = displayText;

	// load dims
	mPosX = mViewport.x;
	mPosY = mViewport.y;
	mWidth = mViewport.w;
	mHeight = mViewport.h;

	
	//  load font and texture
	if(!loadFont())
	{
		mFont = NULL;
	}
	else
	{		
	if(!loadTextTexture(mDisplayText))
		{
			std::string errormsg = "Text field surface could not be loaded";
			SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, errormsg.c_str());
		}
	}
}

	

	
TextField::~TextField()
{
	// free texture & surface

    if ( mDisplaySurface != NULL )
    {
        SDL_FreeSurface( mDisplaySurface );
        mDisplaySurface = NULL;
    }    
    // free title texture
	free();

	
	// free font 
	TTF_CloseFont(mFont);
	mFont = NULL;

}

void TextField::draw()
{
	// draw outline
    SDL_SetRenderDrawColor(Global::appRenderer, 0,0,0,0);
	SDL_RenderDrawRect(Global::appRenderer, &mViewport);

	// set reneder location
	SDL_Rect renderQuad = {mPosX, mPosY, mWidth, mHeight};
	// SDL_RenderSetViewport(Global::appRenderer, &mViewport);


	// copy texture to global renderer
	SDL_RenderCopyEx( 
		Global::appRenderer, mFieldTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);

	// SDL_RenderSetViewport(Global::appRenderer, &SCREEN);
	



}

void TextField::setText(std::string displayText)
{
	// free texture
	free();
	// set text
	mDisplayText = displayText;

	// clean up
	 if ( mDisplaySurface != NULL )
    {
        SDL_FreeSurface( mDisplaySurface );
        mDisplaySurface = NULL;
    }    
    // free title texture
    if ( mFieldTexture != NULL )
    {
        SDL_DestroyTexture( mFieldTexture );
        mFieldTexture = NULL;
    }


	// update surface
	// update texture
	if(!loadTextTexture(mDisplayText))
	{
		std::string errormsg = "Text field surface could not be loaded";
		SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, errormsg.c_str());
	}

}

bool TextField::loadFont()
{
	bool success = true;

	TTF_Font* font = NULL;

	font = TTF_OpenFont(mFormat.fontPath.c_str(), mFormat.fontSize);
	if( font == NULL || TTF_WasInit() == 0 ) // TODO: seperate thesse conditions
	{
		// could not load font
        printf( "Font could not be loaded! Error: %s\n", TTF_GetError() );
        success = false;

	}
	else
	{
		mFont = font;
	}

	return success;

}

bool TextField::loadTextTexture(std::string text) 
{ 
	bool success = true;
    //Set up title surface and texture
	// SDL_Surface* optimizedSurface = NULL;
	free();

    mDisplaySurface = TTF_RenderText_Solid( mFont, mDisplayText.c_str(), mFormat.color );
    // surface creation failed
    if ( mDisplaySurface == NULL )
    {
		success = false;
        printf ( "Could not create surface! SDL Error: %s\n", SDL_GetError() );
    }
	else
	{
		
		mFieldTexture = SDL_CreateTextureFromSurface( Global::appRenderer, mDisplaySurface);
		if (mFieldTexture == NULL)
		{
			printf( "Could not make texture for TextField!\n" );
			success = false;
		}
		else
		{
			mWidth = mDisplaySurface->w;
			mHeight = mDisplaySurface->h;
		}

		// if (TTF_SizeText(mFont, mDisplayText.c_str(), &mWidth, &mHeight) != 0)
		// {
		// 	printf( "Could not make texture for TextField!\n" );
		// 	success = false;
		// }


	}

    return success;

}

void TextField::free(){

	if(mFieldTexture != NULL)
	{
		SDL_DestroyTexture(mFieldTexture);
		mFieldTexture = NULL;
		mWidth = mHeight = 0;
	}

}