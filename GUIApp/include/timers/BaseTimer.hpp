#pragma once
#include "timers/WelfordEstimator.hpp"
#include "timers/HighResolutionTimer.hpp"
#include <thread>

class BaseTimer
{
protected:
	using TimePoint = std::chrono::steady_clock::time_point;

private:
	TimePoint _startTime;
	TimePoint _endTime;
	double _prevFullTimeStep;

#ifdef _DEBUG
	TimePoint _prevCurrentTime;
	double _currentTimeOffset;

	const double _maxDebugPauseTime{ 1.0 };
#endif // _DEBUG

public:
	BaseTimer(double timeStep);

	virtual void startLoop();
	virtual void endLoop();
	virtual double getNextTimeStep() const { return _prevFullTimeStep; }

#ifdef _DEBUG
	virtual void reset() {}
#endif // _DEBUG

protected:
	virtual void computeLoopTimeStep() {}
	void computePrevTimeStep();
	TimePoint getCurrentTime();
	
	const TimePoint& getStartTime() const { return _startTime; }
	const TimePoint& getEndTime() const { return _endTime; }
	double getPrevFullTimeStep() const { return _prevFullTimeStep; }
};
