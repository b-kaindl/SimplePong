#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

// class for rendering textures from images or text

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<string>

#include "Commons/Commons.hpp"
#include "Utils/TextFormat.hpp"
#include "Vectors/Vector2d/Vector2d.hpp"


	
class Texture  
{
	private:

	int mPosX,mPosY;
	int mWidth, mHeight;

	SDL_Texture* mTexture = NULL;
	TTF_Font* mLoadedFont = NULL;
	TextFormat mFormat;


	

	SDL_Texture* loadTexture(TTF_Font* font, std::string& displayText);
	SDL_Texture* loadTexture(std::string& imagePath);
	



	public:
		
		// initialize empty texture --> if texture is to be set via setters
		Texture(int x, int y);

		// initialize texture from font info
		Texture(int x, int y, TTF_Font* font, std::string& displayText);

		// initializing from image
		Texture(int x, int y, std::string& imagePath);

		// destroy texture, surface and FontPointer = NULL
		~Texture();

		void free();
		

		Vector2D getPosition();
		int getWidth();
		int getHeight();

		void setTexture(TTF_Font* font, std::string& displayText);
		void setTexture(std::string& imagePath);

		bool checkTexture();
		void render();

		
		TTF_Font* getFont();


};
#endif