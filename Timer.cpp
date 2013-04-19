#include "Timer.h"
#include "SDL/SDL.h"
#include "Define.h"

// default constructor
Timer::Timer()
{
	startTicks = 0;
	started = false;
}

// set startTicks
void Timer::start()
{
	started = true;
	startTicks = SDL_GetTicks();
}

// stop the timer
void Timer::stop()
{
	started = false;
}

// return the ticks since startTicks
int Timer::get_ticks()
{
	// make sure the timer is running
	if( started ) {
		return SDL_GetTicks() - startTicks;
	}

	// timer is not running
	else return 0;
}

bool Timer::is_started()
{
	return started;
}

void Timer::delay_if_needed()
{
	if( get_ticks() < 1000 / FRAMES_PER_SECOND ) {
		SDL_Delay( (1000 / FRAMES_PER_SECOND) - get_ticks() );
	}
}
