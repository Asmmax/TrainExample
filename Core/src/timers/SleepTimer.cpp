#include "timers/SleepTimer.hpp"
#include "LogManager.hpp"
#include <assert.h>

SleepTimer::SleepTimer(double timeStep, size_t storedFrameCount):
	BaseTimer(timeStep, storedFrameCount),
	_minTimeStep(timeStep),
	_prevLoopTimeStep(timeStep)
{
	_timer.reset();
}

void SleepTimer::endLoop()
{
	const auto& startTime = getStartTime();
	const auto endTime = getCurrentTime();
	const double loopDeltaTime = (endTime - startTime).count() / 1e9;
	LOG_DEBUG_EX("time", "LoopTime = " + std::to_string(loopDeltaTime));
	const double residualSleep = _minTimeStep - loopDeltaTime - _externalTime.getMean();
	if (residualSleep > 0) {
		LOG_DEBUG_EX("time", "ResidualSleepTime = " + std::to_string(residualSleep));
		preciseSleep(residualSleep);
		LOG_DEBUG_EX("time", "SleepTime = " + std::to_string((getCurrentTime() - endTime).count() / 1e9));
	}

	BaseTimer::endLoop();
}

#ifdef _DEBUG
void SleepTimer::reset()
{
	_timer.reset();
	_externalTime.reset();
}
#endif // _DEBUG

void SleepTimer::computeLoopTimeStep()
{
	const auto& startTime = getStartTime();
	const auto& endTime = getEndTime();
	const double prevFullTimeStep = getPrevTimeStep();

	if (startTime.time_since_epoch().count() != 0) {
		_prevLoopTimeStep = (endTime - startTime).count() / 1e9;
	}
	LOG_DEBUG_EX("time", "PrevExternalTime = " + std::to_string(prevFullTimeStep - _prevLoopTimeStep));
	_externalTime.addPoint(prevFullTimeStep - _prevLoopTimeStep);
	LOG_DEBUG_EX("time", "ExternalTime Estimate = " + std::to_string(_externalTime.getMean()));
}

void SleepTimer::preciseSleep(double duration)
{
	const auto startWait = std::chrono::steady_clock::now();
	LOG_DEBUG_PUSH_EX("time", "SleepLoop by process wait");
	_timer.processWait(duration);
	LOG_DEBUG_POP_EX("time");
	const auto endWait = std::chrono::steady_clock::now();
	const double waitTime = (endWait - startWait).count() / 1e9;
	LOG_DEBUG_EX("time", "Process wait time = " + std::to_string(waitTime));

	const double residualTime = duration - waitTime;
	if (residualTime > 0) {
		LOG_DEBUG_EX("time", "Need Spin lock = " + std::to_string(residualTime));
		_timer.spinLock(residualTime);
		LOG_DEBUG_EX("time", "Spin lock time = " + std::to_string((std::chrono::steady_clock::now() - endWait).count() / 1e9));
	}
}
