#ifndef TIMER_H
#define TIMER_h

// timer class to regulate frame rate
class Timer
{
public:
	Timer(); // default constructor

	void start(); // set startTicks to SDL_GetTicks()
	void stop(); // set started = false

	bool is_started(); // return true if started == true

	int get_ticks(); // return the ticks since startTicks

	void delay_if_needed(); // delay if proper delay has not occurred
private:
	int startTicks; // SDL_GetTicks() when the timer was last started
	bool started; // timer status
};

#endif
