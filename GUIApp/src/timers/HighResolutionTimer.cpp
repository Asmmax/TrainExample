#include "timers/HighResolutionTimer.hpp"
#include "LogManager.hpp"
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#include <timeapi.h>
#endif

HighResolutionTimer::HighResolutionTimer()
{
}

void HighResolutionTimer::reset()
{
	_spinLockOffset.reset();
	_sleepTime.reset();
	_sleepTime.addPoint(1e-3);
}

void HighResolutionTimer::processWait(double duration)
{
	if (startProcessWait()) {
		double residualDuration = duration;
		while (residualDuration > _sleepTime.getMean() + 3 * _sleepTime.getDeviation()) {
			const auto start = std::chrono::high_resolution_clock::now();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			const auto end = std::chrono::high_resolution_clock::now();

			const double observed = (end - start).count() / 1e9;

			LOG_DEBUG_EX("time", "Estimate = " + std::to_string(_sleepTime.getMean() + 3 * _sleepTime.getDeviation()));
			LOG_DEBUG_EX("time", "Observed = " + std::to_string(observed));

			_sleepTime.addPoint(observed);

			const auto fullEnd = std::chrono::high_resolution_clock::now();
			residualDuration -= (fullEnd - start).count() / 1e9;
		}
		endProcessWait();
	}
}

void HighResolutionTimer::spinLock(double duration)
{
	const auto start = std::chrono::high_resolution_clock::now();
	while ((std::chrono::high_resolution_clock::now() - start).count() / 1e9 < duration);
}

bool HighResolutionTimer::startProcessWait()
{
#ifdef _WIN32
	const MMRESULT result = timeBeginPeriod(1);
	return result == TIMERR_NOERROR;
#else
	return true
#endif
}

void HighResolutionTimer::endProcessWait()
{
#ifdef _WIN32
	timeEndPeriod(1);
#endif
}
