#include "timers/BaseTimer.hpp"
#include "LogManager.hpp"

BaseTimer::BaseTimer(double timeStep) :
	_prevFullTimeStep(timeStep),
#ifdef _DEBUG
	_currentTimeOffset(0.0)
#endif // _DEBUG
{
}

void BaseTimer::startLoop()
{
	computePrevTimeStep();
	computeLoopTimeStep();
	_startTime = getCurrentTime();
}

void BaseTimer::endLoop()
{
	_endTime = getCurrentTime();
}

void BaseTimer::computePrevTimeStep()
{
	const auto newStartTime = getCurrentTime();

	if (_startTime.time_since_epoch().count() != 0) {
		_prevFullTimeStep = (newStartTime - _startTime).count() / 1e9;
		LOG_DEBUG("Prev real time step = " + std::to_string(_prevFullTimeStep));
	}
}

std::chrono::steady_clock::time_point BaseTimer::getCurrentTime()
{
#ifdef _DEBUG
	auto currentTime = std::chrono::high_resolution_clock::now() - std::chrono::nanoseconds(static_cast<long long>(_currentTimeOffset * 1e9));
	const double duration = (currentTime - _prevCurrentTime).count() / 1e9;
	if (duration > _maxDebugPauseTime) {
		_currentTimeOffset += duration - _maxDebugPauseTime;
		currentTime = std::chrono::high_resolution_clock::now() - std::chrono::nanoseconds(static_cast<long long>(_currentTimeOffset * 1e9));
		reset();
	}
	_prevCurrentTime = currentTime;
	return currentTime;
#else
	return std::chrono::high_resolution_clock::now();
#endif // _DEBUG
}
