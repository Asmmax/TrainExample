#pragma once
#include "WelfordEstimator.hpp"
#include "HighResolutionTimer.hpp"
#include <thread>

class SleepTimer
{
private:
	HighResolutionTimer _timer;

	std::chrono::steady_clock::time_point _startTime;
	std::chrono::steady_clock::time_point _endTime;

#ifdef _DEBUG
	std::chrono::steady_clock::time_point _prevCurrentTime;
	double _currentTimeOffset;

	const double _maxDebugPauseTime{ 1.0 };
#endif // _DEBUG

	double _minTimeStep;
	double _prevLoopTimeStep;
	double _prevFullTimeStep;
	double _residualSleep;

	const int _maxResidualIteration{ 10 };

	WelfordEstimator _sleepTimeOffset;
	WelfordEstimator _loopOffset;

	bool _qualitySync;

public:
	SleepTimer(double timeStep, bool qualitySync);

	void startLoop();
	void endLoop();
	double getNextTimeStep() const;

private:
	void preciseSleep(double duration);
	void computePrevTimeStep();
	std::chrono::steady_clock::time_point getCurrentTime();
};
