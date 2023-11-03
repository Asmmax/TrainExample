#include "SleepTimer.hpp"
#include "LogManager.hpp"
#include <assert.h>

WelfordEstimator::WelfordEstimator():
	_mean(0.0),
	_m2(0.0),
	_stddev(0.0),
	_count(0)
{
}

void WelfordEstimator::addPoint(double observed)
{
	if (_count == 0) {
		init(observed);
		return;
	}

	++_count;
	const double delta = observed - _mean;
	_mean += delta / _count;
	_m2 += delta * (observed - _mean);
	_stddev = sqrt(_m2 / (_count - 1));
}

void WelfordEstimator::reset()
{
	_count = 0;
}

void WelfordEstimator::init(double value)
{
	_mean = value;
	_m2 = 0;
	_count = 1;
}


SleepTimer::SleepTimer(double timeStep, bool qualitySync):
	_minTimeStep(timeStep),
	_prevLoopTimeStep(0.0),
	_prevFullTimeStep(timeStep),
	_residualSleep(0.0),
#ifdef _DEBUG
	_currentTimeOffset(0.0),
#endif // _DEBUG
	_sleepFrequency(0),
	_qualitySync(qualitySync)
{
	init();
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

void SleepTimer::init()
{
	computeSleepTimePeriod(10);

	_sleepFrequency = static_cast<size_t>(round(1.0 / _sleepTimePeriod.getMean()));
	_timeShiftEstimate = getCurrentTime();
}

void SleepTimer::preciseSleep(double duration)
{
	double residualDuration = duration;
	double estimate = getSleepTime();
	LOG_DEBUG_PUSH("SleepLoop by process wait");
	while (residualDuration > estimate) {
		const auto start = getCurrentTime();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		const auto end = getCurrentTime();
		_timeShiftEstimate = end;

		const double observed = (end - start).count() / 1e9;
		residualDuration -= observed;
		
		LOG_DEBUG("Estimate = " + std::to_string(estimate));
		estimate = getSleepTime();
		LOG_DEBUG("Observed = " + std::to_string(observed));
	}
	LOG_DEBUG_POP();
	LOG_DEBUG("Process wait time = " + std::to_string(duration - residualDuration));

	spinLock(residualDuration);
}

void SleepTimer::spinLock(double duration)
{
	if (!_qualitySync){
		return;
	}

	const auto start = getCurrentTime();
	while ((getCurrentTime() - start).count() / 1e9 < duration + _spinLockOffset.getMean());
	auto stop = getCurrentTime();

	const double spinLockTime = (stop - start).count() / 1e9;
	const double observedSpinLockOffset = duration - spinLockTime;
	_spinLockOffset.addPoint(observedSpinLockOffset);
	LOG_DEBUG("Spin lock time = " + std::to_string(spinLockTime));
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

void SleepTimer::computeSleepTimePeriod(int periods)
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

	for (double sleepTime : _sleepTimeSet) {
		_sleepTimePeriod.addPoint(sleepTime);
	}
}

double SleepTimer::getSleepTime() const
{
	const double sleepTimePeriod = 1.0 / _sleepFrequency;
	const auto currentTime = std::chrono::steady_clock::now();
	const double argTimeMin = std::fmod((currentTime - _timeShiftEstimate).count() / 1e9 + 0.5 * _sleepTimeMin, sleepTimePeriod);
	const double argTimeMax = std::fmod((currentTime - _timeShiftEstimate).count() / 1e9 + 1.5 * _sleepTimeMin, sleepTimePeriod);
	const double argTime = std::min(argTimeMin, argTimeMax);
	return _sleepTimeMin + sleepTimePeriod - argTime;
}

std::chrono::steady_clock::time_point SleepTimer::getCurrentTime()
{
#ifdef _DEBUG
	auto currentTime = std::chrono::high_resolution_clock::now() - std::chrono::nanoseconds(static_cast<long long>(_currentTimeOffset * 1e9));
	const double duration = (currentTime - _prevCurrentTime).count() / 1e9;
	if (duration > _maxDebugPauseTime) {
		_currentTimeOffset += duration - _maxDebugPauseTime;
		currentTime = std::chrono::high_resolution_clock::now() - std::chrono::nanoseconds(static_cast<long long>(_currentTimeOffset * 1e9));
		_spinLockOffset.reset();
		_sleepTimeOffset.reset();
		_loopOffset.reset();
}
	_prevCurrentTime = currentTime;
	return currentTime;
#else
	return std::chrono::high_resolution_clock::now();
#endif // _DEBUG
}
