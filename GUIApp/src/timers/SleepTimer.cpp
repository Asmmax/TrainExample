#include "timers/SleepTimer.hpp"
#include "LogManager.hpp"
#include <assert.h>

SleepTimer::SleepTimer(double timeStep):
	BaseTimer(timeStep),
	_sleepTimeOffset(10),
	_loopOffset(10),
	_minTimeStep(timeStep),
	_prevLoopTimeStep(timeStep),
	_residualSleep(0.0)
{
	_timer.reset();
}

void SleepTimer::endLoop()
{
	const auto& startTime = getStartTime();
	const auto endTime = getCurrentTime();
	const double loopDeltaTime = (endTime - startTime).count() / 1e9;
	LOG_DEBUG("LoopTime = " + std::to_string(loopDeltaTime));
	_residualSleep += _minTimeStep - loopDeltaTime - _loopOffset.getMean();
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

	BaseTimer::endLoop();
}

double SleepTimer::getNextTimeStep() const
{
	return std::max(_residualSleep + _minTimeStep + _sleepTimeOffset.getMean(), 0.0);
}

#ifdef _DEBUG
void SleepTimer::reset()
{
	_timer.reset();
	_sleepTimeOffset.reset();
	_loopOffset.reset();
}
#endif // _DEBUG

void SleepTimer::computeLoopTimeStep()
{
	const auto& startTime = getStartTime();
	const auto& endTime = getEndTime();
	const double prevFullTimeStep = getPrevFullTimeStep();

	if (startTime.time_since_epoch().count() != 0) {
		_prevLoopTimeStep = (endTime - startTime).count() / 1e9 + _loopOffset.getMean();
	}
	_loopOffset.addPoint(prevFullTimeStep - _prevLoopTimeStep);
}

void SleepTimer::preciseSleep(double duration)
{
	LOG_DEBUG_PUSH("SleepLoop by process wait");
	const double residualDuration = _timer.processWait(duration);
	LOG_DEBUG_POP();
	LOG_DEBUG("Process wait time = " + std::to_string(duration - residualDuration));
	
	const double lastDuration = _timer.spinLock(residualDuration);
	const double spinLockTime = std::max(residualDuration, 0.0) - std::max(lastDuration, 0.0);
	LOG_DEBUG("Spin lock time = " + std::to_string(spinLockTime));
}
