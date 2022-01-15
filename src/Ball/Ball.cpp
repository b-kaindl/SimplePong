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
        // randomly choose x and y velocity
    // from 
    // https://en.cppreference.com/w/cpp/numeric/random/bernoulli_distribution
    std::random_device rdev;
    std::mt19937_64 gen(rdev());
    std::bernoulli_distribution dist(0.5);

    // flip a coin to choose direction ball goes off in
    bool goesLeft = dist(gen);

    if( goesLeft )
    {
        mVelX = -BALL_VEL;
    }
    else
    {
        mVelX = BALL_VEL;
    }

    // go in straight line
    mVelY = 0;

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
    bool isColliding = (mBallCollider.isColliding(a) || mBallCollider.isColliding(b)); 
    
    if( isColliding )
    {
        mPosX -= (int)(mVelX * deltaTime);
        
        if(abs(mVelX) <= BALL_VEL)
        {
            mVelX = -mVelX;
        }
        else
        {
            // get ball direction
            int direction = std::abs(mVelX) / mVelX;
            mVelX = direction*BALL_VEL;

        }
    }
    else
    {
        mPosX += (int)(mVelX * deltaTime);
    }
    
    
    // TODO: will later become lose condtion
    if( mPosX <= 0 )
    {
       reset();
    }
    
    if( mPosX >= Global::SCREEN_WIDTH + mBallBody.w )  
    {
        // set to max X and change direction
        reset();
    }

    if( isColliding )
    {
        std::stringstream logmsg;
        logmsg << "Ball collision at x: " << mPosX << ", y: " << mPosY << ".\n";
        SDL_LogInfo(SDL_LOG_CATEGORY_TEST,logmsg.str().c_str());
        logmsg.flush();
        mVelY = -mVelY;
        mPosY -= (mVelY * deltaTime);
        logmsg << "Setting Ball to x: " << mPosX << ", y: " << mPosY << ".\n";
        SDL_LogInfo(SDL_LOG_CATEGORY_TEST,logmsg.str().c_str());
        logmsg.flush();


    }
    else
    {
        mPosY += (int)(mVelY*deltaTime);
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
    // cap ball velocity
    if ( std::abs(mVelY) >= BALL_VEL )
    {
        // get ball direction
        int direction = std::abs(mVelY) / mVelY;
        mVelY = direction*BALL_VEL;

    }
    else
    {
        mVelY += velY;
    }

}

void Ball::reset() 
{
    //Initialize position in the center of the screen 
	mPosX = Global::SCREEN_WIDTH/2;
    mPosY = Global::SCREEN_HEIGHT/2;
    
    // Create body to draw
    SDL_Rect body = {(int)mPosX, (int)mPosY, BALL_WIDTH, BALL_HEIGHT};
    mBallBody = body;

    mBallCollider = Collider((int)mPosX, (int)mPosY, BALL_WIDTH, BALL_HEIGHT);
    
    // randomly choose x and y velocity
    // from 
    // https://en.cppreference.com/w/cpp/numeric/random/bernoulli_distribution
    std::random_device rdev;
    std::mt19937_64 gen(rdev());
    std::bernoulli_distribution dist(0.5);

    // flip a coin to choose direction ball goes off in
    bool goesLeft = dist(gen);

    if( goesLeft )
    {
        mVelX = -BALL_VEL;
    }
    else
    {
        mVelX = BALL_VEL;
    }

    // go in straight line
    mVelY = 0;
}

SDL_Rect& Ball::getBallBody() 
{
    return mBallBody;
}
