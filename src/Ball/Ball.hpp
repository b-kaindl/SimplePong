#ifndef BALL_H
#define BALL_H
#pragma once

#include<SDL2/SDL.h>
#include<math.h>
#include<random>

#include "Commons/Commons.hpp"
#include "Collider/Collider.hpp"


class Ball  
{
	public:

		// Ball Dimensions
		static const int BALL_WIDTH =  20;
		static const int BALL_HEIGHT = 20;
		
		//Constuctor - takes in starting position
		Ball(int x = Global::SCREEN_WIDTH/2, int y = Global::SCREEN_HEIGHT/2);

		~Ball();

		// draw to the screen
		void draw();

		// move ball
		void move(SDL_Rect& a, SDL_Rect& b, float deltaTime);

		// get x velocity
		float getVelX();

		// get y velocity
		float getVelY();

		// set y velocity
		void addVelY( float velY );

		// reset ball position
		void reset();

		SDL_Rect& getBallBody();
		

	private:

		// ball body
		SDL_Rect mBallBody;

		// ball collider
		Collider mBallCollider;

		// ball position
		float mPosX, mPosY;

		// current velocity
		float mVelX, mVelY;

		// max velocity
		const int BALL_VEL = 400;


};
#endif