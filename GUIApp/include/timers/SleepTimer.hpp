#pragma once
#include "timers/BaseTimer.hpp"
#include "timers/QueueEstimator.hpp"
#include "timers/HighResolutionTimer.hpp"
#include <thread>

class SleepTimer : public BaseTimer
{
private:
	HighResolutionTimer _timer;
	QueueEstimator _sleepTimeOffset;
	QueueEstimator _loopOffset;

	double _minTimeStep;
	double _prevLoopTimeStep;
	double _residualSleep;

	const int _maxResidualIteration{ 10 };

public:
	SleepTimer(double timeStep);

	void endLoop() override;
	double getNextTimeStep() const override;

#ifdef _DEBUG
	void reset() override;
#endif // _DEBUG

private:
	void computeLoopTimeStep() override;
	void preciseSleep(double duration);
};
