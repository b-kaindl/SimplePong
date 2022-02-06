#include "TextField.hpp"  
	
TextField::TextField(SDL_Rect& fieldRect, TextFormat& fieldFormat, std::string displayText)
{
	// load format
	mFormat = fieldFormat;
	mViewport = fieldRect;
	mDisplayText = displayText;

	mLoadedFont = loadFont();



	Texture* newTexture = new Texture(mViewport.x,mViewport.y, mLoadedFont, displayText);
	mWidth = newTexture->getWidth();
	mHeight = newTexture->getHeight();

	mFieldTexture = newTexture;
}

	

	
TextField::~TextField()
{
	// free texture & surface
	// TTF_Font* textureFont = mFieldTexture->getFont();

	if(mLoadedFont != NULL)
	{
		TTF_CloseFont(mLoadedFont);
	}

	free();
	



}

void TextField::draw()
{
	
	mWidth = mFieldTexture->getWidth();
	mHeight = mFieldTexture->getHeight();
	// set reneder location
	mFieldTexture->render();
	
	// // draw outline
    // SDL_SetRenderDrawColor(Global::appRenderer, 0,0,0,0);
	// SDL_RenderDrawRect(Global::appRenderer, &mViewport);

	// SDL_RenderSetViewport(Global::appRenderer, &SCREEN);
	



}

void TextField::setText(std::string displayText)
{
	// free texture
	free();
	
	// set text
	mDisplayText = displayText;

	// update texture
	loadTextTexture(mDisplayText);
}


void TextField::loadTextTexture(std::string text) 
{ 
	free();
	
    mFieldTexture->setTexture(mLoadedFont, text);
}

void TextField::free(){

	mFieldTexture->free();

}

TTF_Font* TextField::loadFont()
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