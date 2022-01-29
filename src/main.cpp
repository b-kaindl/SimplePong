// Copyright Haruto Kaito - 2021

// Main function - will be run at program start


// includes 

#include<stdio.h>
#include<string>
#include<sstream>

// SDL2
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

// internal includes
#include "Commons/Commons.hpp"
#include "Paddle/Paddle.hpp"
#include "Ball/Ball.hpp"
#include "Timer/Timer.hpp"
#include "TextField/TextField.hpp"
#include "Utils/TextFormat.hpp"


// function prototypes for starting and managing app
bool init();
bool loadResources();
void close();
SDL_Surface* loadTitleSurface( std::string text, SDL_Color fontColor, TTF_Font* font );


// Target Surface
SDL_Surface* gGameTitleSurface = NULL;

// Title
SDL_Texture* gGameTitleTexture = NULL;




// Initialize SDL and create window + renderer
bool init()
{

    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        //could not initialize!
        printf( "Could not initialize SDL! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else 
    {
       // Initialize window 
       Global::appWindow = SDL_CreateWindow( "KaiPong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Global::SCREEN_WIDTH, Global::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
       if( Global::appWindow == NULL )
       {
            // could not create window
            printf( "Failed to initialize window! Error %s\n", SDL_GetError() );
            success = false;
       }
       else
       {
           // Initialize renderer
           Global::appRenderer = SDL_CreateRenderer( Global::appWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
           if( Global::appRenderer == NULL )
           {
                // could not create renderer
                printf( "Failed to initialize renderer! Error %s\n", SDL_GetError() );
                success = false;
           }
           else
           {
                // Initialize draw color - determines window bg color
                SDL_SetRenderDrawColor( Global::appRenderer, 255 , 255 , 255 , 0 );

                // Initialize TTF
                if( TTF_Init() < 0 )
                {
                    printf( "Failed to initialize font engine! Error: %s\n", TTF_GetError() );
                    success = false;
                }
           }
        }
    }



    return success;
}

// loads in font used
bool loadResources() 
{
    bool success = true;

    Global::appFont = TTF_OpenFont( "assets/ProcrastinatingPixie-WyVOO.ttf", 32 );
    if( Global::appFont == NULL )
    {
        // could not load font
        printf( "Font could not be loaded! Error: %s\n", TTF_GetError() );
        success = false;
    }

    // load title surface
    std::string strTitle = "WELCOME TO KAIPONG!";
    SDL_Color titleColor = { 0, 0, 0, 0};
    gGameTitleSurface = loadTitleSurface( strTitle, titleColor, Global::appFont );
    if (gGameTitleSurface == NULL)
    {
        printf( "Could not load surface for title!\n" );
        success = false;
    }

    // assign title texture
    gGameTitleTexture = SDL_CreateTextureFromSurface( Global::appRenderer, gGameTitleSurface );
    if (gGameTitleTexture == NULL)
    {
        printf( "Could not make texture for title!\n" );
        success = false;
    }

    return success;
}

void close() 
{
    // free title surface
    if ( gGameTitleSurface != NULL )
    {
        SDL_FreeSurface( gGameTitleSurface );
        gGameTitleSurface = NULL;
    }    
    // free title texture
    if ( gGameTitleTexture != NULL )
    {
        SDL_DestroyTexture( gGameTitleTexture );
        gGameTitleTexture = NULL;
    }

    // free font
    TTF_CloseFont(Global::appFont);
    Global::appFont = NULL;

    // Destroy window and renderer
    SDL_DestroyRenderer( Global::appRenderer );
    SDL_DestroyWindow( Global::appWindow ); 
    Global::appRenderer = NULL;
    Global::appWindow = NULL;

    // Exit subsystems
    TTF_Quit();
    SDL_Quit();

}

SDL_Surface* loadTitleSurface(std::string text, SDL_Color fontColor, TTF_Font* font) 
{
    // final texture 
    SDL_Texture* titleTexture = NULL;
    
    //Set up title surface and texture
    SDL_Surface* titleSurface = TTF_RenderText_Solid( Global::appFont, text.c_str(), fontColor );

    // surface creation failed
    if ( titleSurface == NULL )
    {
        printf ( "Could not create surface! SDL Error: %s\n", SDL_GetError() );
    }

    return titleSurface;

}


int main( int argc, char const *argv[] )
{
   // Initialize
   if ( !init() )
   {
       printf( "Failed to initialize!\n" );
   }
   else
   {
       if( !loadResources() )
       {
           printf( "Failed loading resources!\n" );
       }
       else
       {

            // main loop flag
            bool quit = false;

            // event handler
            SDL_Event e;

            // initialize paddles

            // Player Rect
            Paddle playerPaddle( 0, Global::SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2, &e );

            // Enemy Rect
            Paddle enemyPaddle(Global::SCREEN_WIDTH - Paddle::PADDLE_WIDTH, Global::SCREEN_HEIGHT / 2 - Paddle::PADDLE_WIDTH / 2 );

            // Ball
            Ball ball;

            // set up text format for scores
            std::string fontPath = "assets/ProcrastinatingPixie-WyVOO.ttf";
            int fontSize = 64;
            SDL_Color fontColor = { 0, 0, 0 }; 

            TextFormat scoreFormat = {fontSize,fontPath,fontColor};

            // Score Tiles
            SDL_Rect leftCorner = {0, 0, Global::SCREEN_WIDTH / 8, Global::SCREEN_HEIGHT / 8};
            SDL_Rect rightCorner = {Global::SCREEN_WIDTH - (Global::SCREEN_WIDTH / 8), 0, Global::SCREEN_WIDTH / 8, Global::SCREEN_HEIGHT / 8};
            int gameScore [2] = {0,0};

            TextField leftScore = TextField(leftCorner, scoreFormat);
            TextField rightScore = TextField(rightCorner, scoreFormat);

            int seed = SDL_GetTicks();
            srand(seed);    // set time-dependent seed everytime on call

            // start timer
            Timer gameTimer;
            gameTimer.start();

            // While application is running
            while( !quit )
            {
                // Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    // user quits
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                        // handle input
                        playerPaddle.handleEvent( e );
                }
                    
                    
                    
                    // TODO: set up render quad for title texture - replace by mechanic driven by states
                    // int titleWidth = gGameTitleSurface->w;
                    // int titleHeight = gGameTitleSurface->h;
                    // SDL_Rect renderQuad = { Global::SCREEN_WIDTH / 2 - (titleWidth / 2), 0, titleWidth, titleHeight };
                    // render title>
                    
                    SDL_SetRenderDrawColor( Global::appRenderer, 0, 0, 0, 0 );

                    // calculate time step in secs
                    float timeStep = gameTimer.getTicks() / 1000.0f;

                    int* newScore;
                    std::stringstream scoreText;

                    // move game forward
                    ball.move(playerPaddle.getPaddleBody(), enemyPaddle.getPaddleBody(), timeStep);
                    playerPaddle.move(ball, timeStep);
                    enemyPaddle.move(ball, timeStep);
                    
                    // compare scores
                    newScore = ball.getCurrentScore();
                    if (*(newScore) != gameScore[0] )
                    {
                        std::string newDisplayText;

                        gameScore[0] = *(newScore);

                        scoreText.flush();
                        scoreText << gameScore[0];
                        leftScore.setText(scoreText.str());
                    }

                    if( *(newScore + 1 ) != gameScore[1] )
                    {
                        std::string newDisplayText;

                        gameScore[1] = *(newScore + 1);

                        scoreText.flush();
                        scoreText << gameScore[1];
                        rightScore.setText(scoreText.str());

                    }
                    



                    // clear screen
                    SDL_SetRenderDrawColor( Global::appRenderer, 255, 255, 255, 255 );
                    SDL_RenderClear( Global::appRenderer );

                    leftScore.draw();
                    
                    rightScore.draw();

                    // restart timer 
                    gameTimer.start();


                    enemyPaddle.trackBall(ball, timeStep );
                    // render paddles
                    SDL_SetRenderDrawColor( Global::appRenderer, 0, 0, 0, 0 );
                    playerPaddle.draw();
                    SDL_SetRenderDrawColor( Global::appRenderer, 0, 0, 0, 0 );
                    enemyPaddle.draw();



                    // render ball
                    SDL_SetRenderDrawColor( Global::appRenderer, 0, 0, 0, 0 );
                    ball.draw();

                    // render midline
                    SDL_SetRenderDrawColor( Global::appRenderer, 0, 0, 0, 0 );
                    SDL_RenderDrawLine( Global::appRenderer, Global::SCREEN_WIDTH / 2, 0, Global::SCREEN_WIDTH / 2, Global::SCREEN_HEIGHT );



                    // Update screen
                    SDL_RenderPresent( Global::appRenderer );
                
            }
       }
    
    close();

   }
    return 0;
}