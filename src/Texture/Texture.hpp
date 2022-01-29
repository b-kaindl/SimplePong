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

	Vector2D mPos;

	int mWidth, mHeight;

	SDL_Texture* mTexture = NULL;
	TTF_Font* mLoadedFont = NULL;
	TextFormat mFormat;

	// load font from member info
	TTF_Font* loadFont();
	

	SDL_Texture* loadTexture(TextFormat& formatInfo, std::string& displayText);
	SDL_Texture* loadTexture(std::string& imagePath);
	



	public:
		
		// initialize empty texture --> if texture is to be set via setters
		Texture(Vector2D& position);

		// initialize texture from font info
		Texture(Vector2D& position, TextFormat& formatInfo, std::string& displayText);

		// initializing from image
		Texture(Vector2D& position, std::string& imagePath);

		// destroy texture, surface and FontPointer = NULL
		~Texture();

		void free();
		

		Vector2D getPosition();
		int getWidth();
		int getHeight();

		void setTexture(TextFormat& formatInfo, std::string& displayText);
		void setTexture(std::string& imagePath);

		bool Texture::checkTexture();
		void render();


};
#endif