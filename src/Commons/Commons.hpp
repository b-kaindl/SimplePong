#ifndef COMMONS_H
#define COMMONS_H
#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>


// global class for variables that haven't been put into their own modules yet

class Global  
{
	public:
		
		static const int SCREEN_WIDTH = 1200;
		static const int SCREEN_HEIGHT = 800;

		static SDL_Window* appWindow;
		static SDL_Renderer* appRenderer;
		static TTF_Font* appFont;

		

};
#endif