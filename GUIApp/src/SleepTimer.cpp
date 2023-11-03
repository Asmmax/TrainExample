#include "SleepTimer.hpp"
#include "LogManager.hpp"
#include <assert.h>

SleepTimer::SleepTimer(double timeStep, bool qualitySync):
	_minTimeStep(timeStep),
	_prevLoopTimeStep(0.0),
	_prevFullTimeStep(timeStep),
	_residualSleep(0.0),
#ifdef _DEBUG
	_currentTimeOffset(0.0),
#endif // _DEBUG
	_qualitySync(qualitySync)
{
	_timer.reset();
}

void SleepTimer::startLoop()
{
	computePrevTimeStep();

	if (_qualitySync) {
		_loopOffset.addPoint(_prevFullTimeStep - _prevLoopTimeStep);
	}

	_startTime = getCurrentTime();
}

void SleepTimer::endLoop()
{
	const auto endTime = getCurrentTime();
	const auto loopDeltaTime = endTime - _startTime;
	LOG_DEBUG("LoopTime = " + std::to_string(loopDeltaTime.count() / 1e9));
	_residualSleep += _minTimeStep - loopDeltaTime.count() / 1e9 - _loopOffset.getMean();
	if (_residualSleep > 0) {
		LOG_DEBUG("ResidualSleepTime = " + std::to_string(_residualSleep));
		preciseSleep(_residualSleep);
		const auto afterSleepTime = getCurrentTime();
		const double sleepTime = (afterSleepTime - endTime).count() / 1e9;
		_sleepTimeOffset.addPoint(sleepTime - _residualSleep);
		LOG_DEBUG("SleepTime = " + std::to_string(sleepTime));
		_residualSleep -= sleepTime;
	}
	_residualSleep = std::max(_residualSleep, -_maxResidualIteration * _minTimeStep);
	if (!_qualitySync) {
		_residualSleep = 0.0;
	}
	_endTime = getCurrentTime();
}

double SleepTimer::getNextTimeStep() const
{
	return std::max(_qualitySync ? _residualSleep + _minTimeStep + _sleepTimeOffset.getMean() : _prevFullTimeStep, 0.0);
}

void SleepTimer::preciseSleep(double duration)
{
	LOG_DEBUG_PUSH("SleepLoop by process wait");
	const double residualDuration = _timer.processWait(duration);
	LOG_DEBUG_POP();
	LOG_DEBUG("Process wait time = " + std::to_string(duration - residualDuration));
	
	if (_qualitySync) {
		const double lastDuration = _timer.spinLock(residualDuration);
		const double spinLockTime = std::max(residualDuration, 0.0) - std::max(lastDuration, 0.0);
		LOG_DEBUG("Spin lock time = " + std::to_string(spinLockTime));
	}
}

void SleepTimer::computePrevTimeStep()
{
	const auto newStartTime = getCurrentTime();

	if (_startTime.time_since_epoch().count() != 0) {
		_prevFullTimeStep = (newStartTime - _startTime).count() / 1e9;
		LOG_DEBUG("Prev real time step = " + std::to_string(_prevFullTimeStep));
		_prevLoopTimeStep = (_endTime - _startTime).count() / 1e9 + _loopOffset.getMean();
	}
}

std::chrono::steady_clock::time_point SleepTimer::getCurrentTime()
{
#ifdef _DEBUG
	auto currentTime = std::chrono::high_resolution_clock::now() - std::chrono::nanoseconds(static_cast<long long>(_currentTimeOffset * 1e9));
	const double duration = (currentTime - _prevCurrentTime).count() / 1e9;
	if (duration > _maxDebugPauseTime) {
		_currentTimeOffset += duration - _maxDebugPauseTime;
		currentTime = std::chrono::high_resolution_clock::now() - std::chrono::nanoseconds(static_cast<long long>(_currentTimeOffset * 1e9));
		_timer.reset();
		_sleepTimeOffset.reset();
		_loopOffset.reset();
}
	_prevCurrentTime = currentTime;
	return currentTime;
#else
	return std::chrono::high_resolution_clock::now();
#endif // _DEBUG
}
