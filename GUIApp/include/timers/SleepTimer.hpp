#pragma once
#include "timers/BaseTimer.hpp"
#include "timers/WelfordEstimator.hpp"
#include "timers/HighResolutionTimer.hpp"
#include <thread>

class SleepTimer : public BaseTimer
{
private:
	HighResolutionTimer _timer;
	WelfordEstimator _externalTime;

	double _minTimeStep;
	double _prevLoopTimeStep;

public:
	SleepTimer(double timeStep, size_t storedFrameCount = 1);

	void endLoop() override;

#ifdef _DEBUG
	void reset() override;
#endif // _DEBUG

private:
	void computeLoopTimeStep() override;
	void preciseSleep(double duration);
};
