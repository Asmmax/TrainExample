#include <thread>
#include <vector>

class WelfordEstimator
{
private:
	double _mean;
	double _m2;
	double _stddev;
	size_t _count;

public:
	WelfordEstimator();

	void addPoint(double observed);
	void reset();
	double getMean() const { return _mean; }
	double getDeviation() const { return _stddev; }

private:
	void init(double value);
};

class SleepTimer
{
private:
	std::chrono::steady_clock::time_point _startTime;
	std::chrono::steady_clock::time_point _endTime;
	std::chrono::steady_clock::time_point _timeShiftEstimate;

#ifdef _DEBUG
	std::chrono::steady_clock::time_point _prevCurrentTime;
	double _currentTimeOffset;

	const double _maxDebugPauseTime{ 1.0 };
#endif // _DEBUG

	double _minTimeStep;
	double _prevLoopTimeStep;
	double _prevFullTimeStep;
	double _residualSleep;

	size_t _sleepFrequency;

	const double _sleepTimeMin{ 1e-3 };
	const int _maxResidualIteration{ 10 };

	WelfordEstimator _spinLockOffset;
	WelfordEstimator _sleepTimeOffset;
	WelfordEstimator _loopOffset;
	WelfordEstimator _sleepTimePeriod;

	bool _qualitySync;

public:
	SleepTimer(double timeStep, bool qualitySync);

	void startLoop();
	void endLoop();
	double getNextTimeStep() const;

private:
	void init();
	void preciseSleep(double duration);
	void spinLock(double duration);
	void computePrevTimeStep();
	void computeSleepTimePeriod(int periods);
	double getSleepTime() const;
	std::chrono::steady_clock::time_point getCurrentTime();
};
