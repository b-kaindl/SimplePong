#ifndef PTEXTURE_H
#define PTEXTURE_H
#pragma once

#include<string>

// SDL2
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

#include "Commons/Commons.hpp"


class PTexture  
{
	private:

	// position and dimensions
	int mWidth,mHeight;

	// actual hardware texture
	SDL_Texture* mTexture;

	// Frees Texture
	void free();

	


	

	public:

		PTexture();
		~PTexture();

		// loads image from file
		bool loadFromFile( std::string filePath );

		int getWidth();
		int getHeight();

		void render(int x, int y);


};
#endif