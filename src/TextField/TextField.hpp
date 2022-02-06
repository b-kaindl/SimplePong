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
#include "Texture/Texture.hpp"
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
		Texture* mFieldTexture = NULL;

		// format info
		TextFormat mFormat;

		TTF_Font* mLoadedFont;


		// free texture and
		void free();
		

		// load texture from text
		void loadTextTexture(std::string text);

		// load font from member info
		TTF_Font* loadFont();


	public:

		// constructor
		TextField(SDL_Rect& fieldRect, TextFormat& fieldFormat, std::string displayText="x");

		// destructor
		~TextField();

		// draw method -> renders texture to screen
		void draw();

		// change text and update texture
		void setText(std::string displayText);

		// optional --> update method for format
		

};
#endif