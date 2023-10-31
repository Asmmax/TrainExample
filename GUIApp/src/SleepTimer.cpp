#include "SleepTimer.hpp"

SleepTimer::SleepTimer(double timeStep):
	_minTimeStep(timeStep),
	_residualSleep(0.0),
	_estimate(5e-3),
	_mean(5e-3),
	_m2(0.0),
	_count(1)
{
}

void SleepTimer::startLoop()
{
	_startTime = std::chrono::high_resolution_clock::now();
}

void SleepTimer::endLoop()
{
	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto loopDeltaTime = endTime - _startTime;
	_residualSleep += _minTimeStep - loopDeltaTime.count() / 1e9;
	if (_residualSleep > 0) {
		preciseSleep(_residualSleep);
		const auto afterSleepTime = std::chrono::high_resolution_clock::now();
		const auto sleepTime = afterSleepTime - endTime;
		_residualSleep -= sleepTime.count() / 1e9;
	}
}

// Uses Welford's online algorithm to estimate sleep time
void SleepTimer::preciseSleep(double duration)
{
	while (duration > _estimate) {
		const auto start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		const auto end = std::chrono::high_resolution_clock::now();

		const double observed = (end - start).count() / 1e9;
		duration -= observed;

		++_count;
		const double delta = observed - _mean;
		_mean += delta / _count;
		_m2 += delta * (observed - _mean);
		const double stddev = sqrt(_m2 / (_count - 1));
		_estimate = _mean + stddev;
	}

	// spin lock
	const auto start = std::chrono::high_resolution_clock::now();
	while ((std::chrono::high_resolution_clock::now() - start).count() / 1e9 < duration);
}
