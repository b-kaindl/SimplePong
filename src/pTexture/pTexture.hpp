#ifndef PTEXTURE_H
#define PTEXTURE_H
#pragma once

#include<string>

// SDL2
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

#include "Commons/Commons.hpp"


class pTexture  
{
	private:

	int mPosX,mPosY,mWidth,mHeight;

	SDL_Texture* mTextures;


	

	public:

		pTexture();
		~pTexture();

		int getWidth();
		int getHeight();

		void render();


};
#endif