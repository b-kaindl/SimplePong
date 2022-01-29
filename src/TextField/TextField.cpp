#include "TextField.hpp"  
	
TextField::TextField(SDL_Rect& fieldRect, TextFormat& fieldFormat, std::string displayText)
{
	// load format
	mFormat = fieldFormat;
	mViewport = fieldRect;
	mDisplayText = displayText;

	// load dims
	mPos = {fieldRect.x,fieldRect.y};
	mFieldTexture = &(Texture(mPos, fieldFormat, displayText));

	

}

	

	
TextField::~TextField()
{
	// free texture & surface
	mFieldTexture->free();



}

void TextField::draw()
{
	// draw outline
    SDL_SetRenderDrawColor(Global::appRenderer, 0,0,0,0);
	SDL_RenderDrawRect(Global::appRenderer, &mViewport);

	// set reneder location
	mFieldTexture->render();
	

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
	
    mFieldTexture->setTexture(mFormat, text);
}

void TextField::free(){

	mFieldTexture->free();

}