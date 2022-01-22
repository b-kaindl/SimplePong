#ifndef TEXTFORMAT_H_
#define TEXTFORMAT_H_
#include<string>
#include<SDL2/SDL.h>



struct TextFormat
{
	int fontSize;
	std::string fontPath ;
	SDL_Color color;
};
	

#endif /*TEXTFORMAT_H_*/
