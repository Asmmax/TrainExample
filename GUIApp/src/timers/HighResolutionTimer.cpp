#include "timers/HighResolutionTimer.hpp"
#include "LogManager.hpp"
#include <vector>
#include <Windows.h>
#include <timeapi.h>
#include <assert.h>

HighResolutionTimer::HighResolutionTimer()
{
}

void HighResolutionTimer::reset()
{
	_spinLockOffset.reset();
	computeSleepTimePeriod(1);
}

double HighResolutionTimer::processWait(double duration)
{
	const auto startWait = std::chrono::high_resolution_clock::now();
	MMRESULT result = timeBeginPeriod(1);
	double dbgDuration = 0.0;
	if (result == TIMERR_NOERROR) {
		double residualDuration = duration;
		double estimate = getSleepTime();
		while (residualDuration > estimate) {
			const auto start = std::chrono::high_resolution_clock::now();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			const auto end = std::chrono::high_resolution_clock::now();
			accurizeSleepTimePeriod((end - _timeShiftEstimate).count() / 1e9);
			_timeShiftEstimate = end;

			const double observed = (end - start).count() / 1e9;

			const auto startDbg = std::chrono::high_resolution_clock::now();
			LOG_DEBUG("Estimate = " + std::to_string(estimate));
			LOG_DEBUG("Observed = " + std::to_string(observed));
			const auto endDbg = std::chrono::high_resolution_clock::now();
			dbgDuration += (endDbg - startDbg).count() / 1e9;

			estimate = getSleepTime();
			const auto fullEnd = std::chrono::high_resolution_clock::now();
			residualDuration -= (fullEnd - start).count() / 1e9;
		}
		timeEndPeriod(1);
	}
	const auto endWait = std::chrono::high_resolution_clock::now();
	const double diff = duration - (endWait - startWait).count() / 1e9;
	assert(dbgDuration < 0.0006);
	return diff;
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
	const double sleepTimePeriod = 1.0 / round(1.0 / _sleepTimePeriod.getMean());
	const auto currentTime = std::chrono::steady_clock::now();
	const double argTimeMin = std::fmod((currentTime - _timeShiftEstimate).count() / 1e9 + _sleepTimeMin - _relativeTimeShift, sleepTimePeriod);
	const double argTimeMax = std::fmod((currentTime - _timeShiftEstimate).count() / 1e9 + _sleepTimeMin + _relativeTimeShift, sleepTimePeriod);
	const double argTime = min(argTimeMin, argTimeMax);
	return _sleepTimeMin + sleepTimePeriod - argTime;
}

void HighResolutionTimer::computeSleepTimePeriod(int periods)
{
	MMRESULT result = timeBeginPeriod(1);
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
	if (result == TIMERR_NOERROR) {
		timeEndPeriod(1);
	}

	_sleepTimePeriod.reset();
	for (double sleepTime : _sleepTimeSet) {
		_sleepTimePeriod.addPoint(sleepTime);
	}
}

void HighResolutionTimer::accurizeSleepTimePeriod(double somePeriods)
{
	const double invRelativeErr = _sleepTimePeriod.getMean() / _sleepTimePeriod.getDeviation();
	if (invRelativeErr < 9.0) {
		return;
	}

	const double Nmax = invRelativeErr / 6 - 0.5;
	const double realN = round(somePeriods / _sleepTimePeriod.getMean());
	if (realN > Nmax) {
		return;
	}
	const double period = somePeriods / realN;
	for (int i = 0; i < static_cast<int>(realN*realN); i++) {
		_sleepTimePeriod.addPoint(period);
	}
}
