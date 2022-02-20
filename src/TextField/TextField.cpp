#include "TextField.hpp"  
	
TextField::TextField(int x, int y, TextFormat& fieldFormat, std::string displayText)
{
	// load format
	mFormat = fieldFormat;
	mDisplayText = displayText;
	mFieldTexture = new PTexture;
	mFieldTexture->loadFromRenderedText(mFormat.font, mDisplayText, mFormat.color);
	mWidth = mFieldTexture->getWidth();
	mHeight = mFieldTexture->getHeight();
	mViewport = {x,y, mWidth, mHeight};

	
}

	

	
TextField::~TextField()
{

}

void TextField::draw()
{
	
	mWidth = mFieldTexture->getWidth();
	mHeight = mFieldTexture->getHeight();
	// set render location
	mFieldTexture->render(mViewport.x, mViewport.y);



}

void TextField::setText(std::string displayText)
{	
	// set text
	mDisplayText = displayText;

	// update texture
	mFieldTexture->loadFromRenderedText(mFormat.font, mDisplayText, mFormat.color);

}

int TextField::getWidth()
{
	return mWidth;
}

int TextField::getHeight()
{
	return mHeight;
}