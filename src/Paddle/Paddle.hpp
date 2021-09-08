#ifndef PADDLE_H
#define PADDLE_H
#pragma once

#include<SDL2/SDL.h>
#include<stdlib.h> //for rand()

#include "Commons/Commons.hpp"
#include "Vectors/Vector2d/Vector2d.hpp"
#include "Collider/Collider.hpp"
// HACK: probably better to include it somewhere else
#include "Ball/Ball.hpp"

// IDEA: add collision rect and check for collision
// simulate impact using Ball::addVelY() via collider
class Paddle  
{
	public:

		// Paddle Dimensions
		static const int PADDLE_WIDTH = 20;
		static const int PADDLE_HEIGHT = 200;

		// Constructor
		Paddle(int x, int y, SDL_Event* event = NULL );

		// Destructor
		~Paddle();

		// draw to the screen
		void draw();

		// TODO: handle event - move to player class later || think of other implementation - this gets awkward
		void handleEvent(SDL_Event& e);

		// TODO: method to have enemy paddle track the ball - refactor later
		void trackBall(Ball& ball, float deltaTime );

		// move paddle - move event handler into player controller later on
		void move( Ball& ball, float deltaTime );

		// get body for collision detection - contains everything we need
		SDL_Rect& getPaddleBody();


	private:

		// Paddle Body and collider
		SDL_Rect mPaddleBody;
		Collider mPaddleCollider; 

		// current paddle position
		int mPosX;
		int mPosY;

		// current velocity
		int mVel;

		// optional player controller
		SDL_Event* mE = NULL;

		// max velocity
		const int PADDLE_VEL = 3;




};
#endif