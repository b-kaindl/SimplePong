/*
 * Timer.cpp
 *
 *  Created on: Sep 6, 2021
 *      Author: kaiharuto
 */

#include "Timer.hpp"

Timer::Timer() {

	mStartTicks = 0;
	mPausedTicks = 0;

	mStarted = false;
	mPaused = false;

}

void Timer::start()
{
	// start
	mStarted = true;

	// unpause
	mPaused = false;

	// get current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}


void Timer::stop()
{
	// start and paused to false
	mStarted = mPaused = false;

	// reset timestamps
	mStartTicks = mPausedTicks = 0;

}

void Timer::pause()
{
	if( mStarted && !mPaused)
	{
		// pause
		mPaused = true;

		// calculate paused ticks and reset Start ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;

	}

}	


void Timer::unpause()
{
	if( mStarted && mPaused)
	{
		// set pause flag to false
		mPaused = false;
 
		// set new start ticks 
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		// reset paused ticks
		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks() 
{
	// actual timer time
	Uint32 time = 0;

	// if timer is running
	if( mStarted )
	{
		// if timer is paused
		if ( mPaused )
		{
			// return ticks at pause time
			time = mPausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool Timer::isStarted() 
{
	return mStarted;
}

bool Timer::isPaused() 
{
	return mPaused;
}
