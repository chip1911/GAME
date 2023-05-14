#ifndef L_TIMER_H_
#define L_TIMER_H_

class LTimer
{
public:
	LTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	int getTicks(); // get the timer's time

	bool isStarted();
	bool isPaused();
	int getPause();


private:
	int mStartTicks;

	int mPausedTicks;

	bool mPaused;
	bool mStarted;

};
#endif