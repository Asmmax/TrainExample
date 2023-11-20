#pragma once
#include "timers/WelfordEstimator.hpp"
#include <thread>

class HighResolutionTimer
{
private:
	WelfordEstimator _spinLockOffset;
	WelfordEstimator _sleepTime;

public:
	HighResolutionTimer();

	void reset();
	void processWait(double duration);
	void spinLock(double duration);

public:
	bool startProcessWait();
	void endProcessWait();
};
