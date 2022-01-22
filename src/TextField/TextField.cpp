#include "TextField.hpp"  
	
TextField::TextField(SDL_Rect& fieldRect, TextFormat& fieldFormat, std::string displayText)
{
	// load format
	mFormat = fieldFormat;
	mViewport = fieldRect;
	mDisplayText = displayText;
	
	//  load font and texture
	if(!loadFont())
	{
		mFont = NULL;
	}
	else
	if(!loadTextTexture(mDisplayText))
	{
		std::string errormsg = "Text field surface could not be loaded";
		SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, errormsg.c_str());
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
    if ( mFieldTexture != NULL )
    {
        SDL_DestroyTexture( mFieldTexture );
        mFieldTexture = NULL;
    }

	
	// free font 
	TTF_CloseFont(mFont);
	mFont = NULL;

}

void TextField::draw()
{
	// set viewport
	SDL_RenderSetViewport(Global::appRenderer, &mViewport);
	
	// copy texture to global renderer
	SDL_RenderCopy( Global::appRenderer, mFieldTexture, NULL, NULL);
	
	// reset viewport
	SDL_Rect screenRect;
	screenRect.x = screenRect.y = 0;
	screenRect.w = Global::SCREEN_WIDTH;
	screenRect.h = Global::SCREEN_HEIGHT;

	SDL_RenderSetViewport(Global::appRenderer, &screenRect);

}

void TextField::setText(std::string displayText)
{
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
	}

    return success;

}