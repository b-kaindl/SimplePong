#ifndef TEXTFORMAT_H_
#define TEXTFORMAT_H_
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>




struct TextFormat
{
	TTF_Font* font;
	SDL_Color color;
};
	

#endif /*TEXTFORMAT_H_*/
