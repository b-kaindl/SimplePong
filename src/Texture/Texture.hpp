#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

// class for rendering textures from images or text

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<string>

#include "Commons/Commons.hpp"
#include"Utils/TextFormat.hpp"


	
class Texture  
{
	private:

	int mWidth, mHeight;

	SDL_Texture* mTexture = NULL;
	TTF_Font* mLoadedFont = NULL;
	TextFormat mFormat;

	// load font from member info
	TTF_Font* loadFont();
	
	void free();
	



	public:
		
		// initialize empty texture --> if texture is to be set via setters
		Texture();

		// initialize texture from font info
		Texture(TextFormat& formatInfo, std::string& displayText);

		// initializing from image
		Texture(std::string& imagePath);

		// destroy texture, surface and FontPointer = NULL
		~Texture();

		SDL_Texture* loadTexture(TextFormat& formatInfo, std::string& displayText);
		SDL_Texture* loadTexture(std::string& imagePath);

		void render();


};
#endif