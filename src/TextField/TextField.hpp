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

// struct to hold formatting info for text
struct TextFormat
{
	int fontSize;
	TTF_Font* font;
	SDL_Color color;

};
	
class TextField  
{
	private:

		// Dimensions & Postion
		int mPosX, mPosY, mWidth, mHeight;
	
		// Viewport
		SDL_Rect mViewport;

		// text to display
		std::string mDisplayText;

		// surface object to render
		SDL_Surface* mDisplaySurface;

		// texture object
		SDL_Texture* mFieldTexture;

		// format info
		TextFormat mFormat;

		// font asset retrieval
		TTF_Font* loadFont( std::string path);

	public:

		// constructor
		TextField(SDL_Rect& fieldRect, std::string fontPath, 
		TextFormat fieldFormat, std::string displayText="x");

		// destructor
		~TextField();

		// draw method -> renders texture to screen
		void draw();

		void setText(std::string displayText);

};
#endif