#include "Ball.hpp"  

Ball::Ball(int x, int y)
{
    //Initialize position
	mPosX = x;
    mPosY = y;
    
    // Create body to draw
    SDL_Rect body = {(int)mPosX, (int)mPosY, BALL_WIDTH, BALL_HEIGHT};
    mBallBody = body;

    mBallCollider = Collider((int)mPosX, (int)mPosY, BALL_WIDTH + 1, BALL_HEIGHT + 1);
    
    // set constant velocity for both x and y
    mVelX = mVelY = BALL_VEL;

}

	
Ball::~Ball()
{
	
}

void Ball::draw() 
{     
        // have the global renderer fill the rectangle
        SDL_RenderFillRect(Global::appRenderer, &mBallBody);
}

void Ball::move(SDL_Rect& a, SDL_Rect& b, float deltaTime)
{
    bool isColliding =(mBallCollider.isColliding(a) || mBallCollider.isColliding(b)); 
    
    if( isColliding )
    {
        mPosX -= mVelX * deltaTime;
        mVelX = -mVelX;
    }
    else
    {
        mPosX += mVelX * deltaTime;
    }
    
    
    // TODO: will later become lose condtion
    if( mPosX < 0 )
    {
       reset();
    }
    
    if( mPosX > Global::SCREEN_WIDTH - mBallBody.w )  
    {
        // set to max X and change direction
        reset();
    }

    if( isColliding )
    {
        mPosY -= mVelY;
        mVelY = -mVelY;
    }
    else
    {
        mPosY += mVelY*deltaTime;
    }
    

    if( mPosY < 0 )
    {
        // set to 0 and change direction
        mPosY = 0;
        mVelY = -mVelY;

    }
    
    if( mPosY > Global::SCREEN_HEIGHT - mBallBody.h )  
    {
        // set to max X and change direction
        mPosY = Global::SCREEN_HEIGHT - mBallBody.h;
        mVelY = -mVelY;
    }

    mBallBody = {(int)mPosX, (int)mPosY, BALL_WIDTH, BALL_HEIGHT};
    // IDEA: use reference to ballbody for automatic updating
    mBallCollider.setCollisionRect(mBallBody);

}

float Ball::getVelX() 
{
    return mVelX;
}

float Ball::getVelY() 
{
    return mVelY;
}

void Ball::addVelY(float velY) 
{
    mVelY += velY;
}

void Ball::reset() 
{
        //Initialize position
	mPosX = 0;
    mPosY = 0;
    
    // Create body to draw
    SDL_Rect body = {(int)mPosX, (int)mPosY, BALL_WIDTH, BALL_HEIGHT};
    mBallBody = body;

    mBallCollider = Collider((int)mPosX, (int)mPosY, BALL_WIDTH, BALL_HEIGHT);
    
    // set constant velocity for both x and y
    mVelX = mVelY = BALL_VEL;
}

SDL_Rect& Ball::getBallBody() 
{
    return mBallBody;
}
