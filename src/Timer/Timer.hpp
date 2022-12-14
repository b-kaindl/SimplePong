
#ifndef TIMER_H_
#define TIMER_H_
#pragma once

#include<SDL2/SDL.h>

class Timer {
public:
	// Initialize variables
	Timer();

	// Timer Controls
	void start();
	void stop();
	void pause();
	void unpause();

	// Get time
	Uint32 getTicks();

	// Get status
	bool isStarted();
	bool isPaused();

private:
	// ticks at clock start time
	Uint32 mStartTicks;

	// ticks when timer was paused
	Uint32 mPausedTicks;

	// timer status
	bool mPaused;
	bool mStarted;


};

#endif /* TIMER_H_ */
