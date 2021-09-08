#include "Paddle.hpp"  
	
Paddle::Paddle(int x, int y, SDL_Event* event)
{
        // If listener event was passed, set it
        if( event != NULL)
        {
            mE = event;
        }
        // Initialize members
        mPosX = x;
        mPosY = y;
        mVel = 0;
        SDL_Rect body = {x, y, PADDLE_WIDTH, PADDLE_HEIGHT};
        mPaddleBody = body;
        mPaddleCollider = Collider(mPosX, mPosY, PADDLE_WIDTH, PADDLE_HEIGHT);

        
}
	
Paddle::~Paddle()
{
	if(mE != NULL)
    {
        // clean up event if assigned
        mE = NULL;
    }
}

void Paddle::draw() 
{     
        // have the global renderer draw the rectangle
        SDL_RenderDrawRect(Global::appRenderer, &mPaddleBody);
}

void Paddle::handleEvent(SDL_Event& e) 
{
    if(mE != NULL)
    {
        if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_UP: mVel -= PADDLE_VEL; break;
                case SDLK_DOWN: mVel += PADDLE_VEL; break;
            }
        }

        else if(e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_UP: mVel += PADDLE_VEL; break;
                case SDLK_DOWN: mVel -= PADDLE_VEL; break;
            }
        }
    }
}

// IDEA: track projected impact point rather than current ball height
void Paddle::trackBall(Ball& ball, float deltaTime) 
{
    // draw a random value of up to +/- [errorFactor] paddle heights
    const float errorFactor = 2.8f;
    int error = (rand() % (ball.getBallBody().w)) * errorFactor - (int)(ball.getBallBody().w * errorFactor );

    // only track once ball crossed the middle

    if( ball.getBallBody().x + ball.getBallBody().w  / 2 > Global::SCREEN_WIDTH / 2 )
    {

        // if ball is higher
        if( (ball.getBallBody().y + ball.getBallBody().h) + (int)error < mPosY )
        {
            // move up
            // mVel = 0;
            mVel -= PADDLE_VEL;
        }

        // if ball is lower
        if( ball.getBallBody().y  + (int)error   > (int)mPosY + PADDLE_HEIGHT)
        {
            // move down
            // mVel = 0;
            mVel += PADDLE_VEL;
        }
    }
    else
    {
        mVel = 0;
    }
}



void Paddle::move(Ball& ball, float deltaTime) 
{
    //check for bounds
    mPosY += mVel;

    //simulate simple friction
    float friction = 5;
    
    if(mPosY <  0)
    {
        mPosY = 0;
    }
    
    if(mPosY > Global::SCREEN_HEIGHT - mPaddleBody.h )
    {
        mPosY = Global::SCREEN_HEIGHT - mPaddleBody.h;
    }

    // pass on velocity
    if(mPaddleCollider.isColliding(ball.getBallBody()))
    {
        // calculate passed velocity
        int passedVel = (int)(mVel * 1.0f/friction);
        ball.addVelY(passedVel);
    }

    mPaddleBody = {(int)mPosX, (int)mPosY, PADDLE_WIDTH, PADDLE_HEIGHT};
    mPaddleCollider.setCollisionRect(mPaddleBody);
    
}

SDL_Rect& Paddle::getPaddleBody() 
{
    return mPaddleBody;
}

