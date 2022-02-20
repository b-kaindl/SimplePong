#ifndef TEXTFIELD_H
#define TEXTFIELD_H
#pragma once

// includes

#include<stdio.h>
#include<string>

// SDL2
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

// internal includes
#include "Commons/Commons.hpp"
#include "PTexture/PTexture.hpp"
#include "Utils/TextFormat.hpp"
#include "Vectors/Vector2d/Vector2d.hpp"
	
class TextField  
{
	private:

		// Dimensions & Postion
		int x, y;
		int mWidth, mHeight;
	
		// Viewport
		SDL_Rect mViewport;

		// text to display
		std::string mDisplayText;

		// texture object
		PTexture* mFieldTexture;

		// format info
		TextFormat mFormat;
	

		// load texture from text
		void updateTextTexture(std::string text);





	public:

		// constructor
		TextField(int x, int y, TextFormat& fieldFormat, std::string displayText="x");

		// destructor
		~TextField();

		// draw method -> renders texture to screen
		void draw();

		// change text and update texture
		void setText(std::string displayText);

		// get width and height
		int getWidth();
		int getHeight();
		

};
#endif