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

	double _minTimeStep;
	double _prevLoopTimeStep;
	double _prevFullTimeStep;
	double _residualSleep;

	size_t _sleepFrequency;
	const double _sleepTimeMin{ 1e-3 };

	WelfordEstimator _spinLockOffset;
	WelfordEstimator _sleepTimeOffset;
	WelfordEstimator _loopOffset;

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
	double getSleepTime() const;
};
