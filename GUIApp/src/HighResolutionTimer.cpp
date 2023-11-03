#include "HighResolutionTimer.hpp"
#include "LogManager.hpp"
#include <vector>

HighResolutionTimer::HighResolutionTimer() :
	_sleepFrequency(0)
{
}

void HighResolutionTimer::reset()
{
	_spinLockOffset.reset();
	computeSleepTimePeriod(10);
	_sleepFrequency = static_cast<size_t>(round(1.0 / _sleepTimePeriod.getMean()));
}

double HighResolutionTimer::processWait(double duration)
{
	double residualDuration = duration;
	double estimate = getSleepTime();
	while (residualDuration > estimate) {
		const auto start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		const auto end = std::chrono::high_resolution_clock::now();
		accurizeSleepTimePeriod((end - _timeShiftEstimate).count() / 1e9);
		_timeShiftEstimate = end;

		const double observed = (end - start).count() / 1e9;
		residualDuration -= observed;

		LOG_DEBUG("Estimate = " + std::to_string(estimate));
		LOG_DEBUG("Observed = " + std::to_string(observed));

		estimate = getSleepTime();
	}
	return residualDuration;
}

double HighResolutionTimer::spinLock(double duration)
{
	const auto start = std::chrono::high_resolution_clock::now();
	while ((std::chrono::high_resolution_clock::now() - start).count() / 1e9 < duration + _spinLockOffset.getMean());
	auto stop = std::chrono::high_resolution_clock::now();

	const double spinLockTime = (stop - start).count() / 1e9;
	const double observedSpinLockOffset = duration - spinLockTime;
	_spinLockOffset.addPoint(observedSpinLockOffset);
	return observedSpinLockOffset;
}

double HighResolutionTimer::getSleepTime() const
{
	const double sleepTimePeriod = 1.0 / _sleepFrequency;
	const auto currentTime = std::chrono::steady_clock::now();
	const double argTimeMin = std::fmod((currentTime - _timeShiftEstimate).count() / 1e9 + _sleepTimeMin - _relativeTimeShift, sleepTimePeriod);
	const double argTimeMax = std::fmod((currentTime - _timeShiftEstimate).count() / 1e9 + _sleepTimeMin + _relativeTimeShift, sleepTimePeriod);
	const double argTime = std::min(argTimeMin, argTimeMax);
	return _sleepTimeMin + sleepTimePeriod - argTime;
}

void HighResolutionTimer::computeSleepTimePeriod(int periods)
{
	std::vector<double> _sleepTimeSet;
	_sleepTimeSet.resize(periods);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < periods; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		const auto end = std::chrono::high_resolution_clock::now();
		_sleepTimeSet[i] = (end - start).count() / 1e9;
		start = end;
	}
	_timeShiftEstimate = start;

	_sleepTimePeriod.reset();
	for (double sleepTime : _sleepTimeSet) {
		_sleepTimePeriod.addPoint(sleepTime);
	}
}

void HighResolutionTimer::accurizeSleepTimePeriod(double somePeriods)
{
	if (somePeriods < _sleepTimePeriod.getMax()) {
		_sleepTimePeriod.addPoint(somePeriods);
		_sleepFrequency = static_cast<size_t>(round(1.0 / _sleepTimePeriod.getMean()));
		return;
	}
}
