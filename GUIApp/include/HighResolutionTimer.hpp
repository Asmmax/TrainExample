#pragma once
#include "WelfordEstimator.hpp"
#include <thread>

class HighResolutionTimer
{
private:
	std::chrono::steady_clock::time_point _timeShiftEstimate;

	WelfordEstimator _spinLockOffset;
	WelfordEstimator _sleepTimePeriod;

	size_t _sleepFrequency;

	const double _sleepTimeMin{ 1e-3 };
	const double _relativeTimeShift{ 5e-4 };

public:
	HighResolutionTimer();

	void reset();
	double processWait(double duration);
	double spinLock(double duration);
	double getSleepTime() const;

private:
	void computeSleepTimePeriod(int periods);
	void accurizeSleepTimePeriod(double somePeriods);
};
