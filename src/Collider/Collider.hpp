#ifndef COLLIDER_H
#define COLLIDER_H
#pragma once

#include<SDL2/SDL.h>
	
class Collider  
{
	public:
		
		Collider();
		Collider(int x, int y, int w, int h);
		~Collider();

		// detect collisions with other colliders
		bool isColliding(SDL_Rect& otherRect);

		void setCollisionRect(SDL_Rect& rect);

	private:

	SDL_Rect mCollisionRect;


};
#endif