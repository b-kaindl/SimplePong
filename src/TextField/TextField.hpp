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
#include "Utils/TextFormat.hpp"
	
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

		// actual font used
		TTF_Font* mFont;

		// font asset retrieval
		bool loadFont();

		// load texture from text
		bool loadTextTexture(std::string text);

	public:

		// constructor
		TextField(SDL_Rect& fieldRect, TextFormat& fieldFormat, std::string displayText="x");

		// destructor
		~TextField();

		// draw method -> renders texture to screen
		void draw();

		void setText(std::string displayText);

		// optional --> update method for format
		

};
#endif