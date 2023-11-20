#pragma once
#include "timers/QueueAverager.hpp"
#include "timers/HighResolutionTimer.hpp"
#include <thread>

class BaseTimer
{
protected:
	using TimePoint = std::chrono::steady_clock::time_point;

private:
	TimePoint _startTime;
	TimePoint _endTime;
	QueueAverager _nextTimeStep;
	double _prevTimeStep;

#ifdef _DEBUG
	TimePoint _prevCurrentTime;
	double _currentTimeOffset;

	const double _maxDebugPauseTime{ 1.0 };
#endif // _DEBUG

public:
	BaseTimer(double timeStep, size_t storedFrameCount = 1);

	virtual void startLoop();
	virtual void endLoop();

	double getNextTimeStep() const;

#ifdef _DEBUG
	virtual void reset() {}
#endif // _DEBUG

protected:
	virtual void computeLoopTimeStep() {}
	void computePrevTimeStep(const TimePoint& newStartTime);
	TimePoint getCurrentTime();
	
	const TimePoint& getStartTime() const { return _startTime; }
	const TimePoint& getEndTime() const { return _endTime; }
	double getPrevTimeStep() const { return _prevTimeStep; }
};
