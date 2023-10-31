#include <thread>

class SleepTimer
{
private:
	std::chrono::steady_clock::time_point _startTime;

	double _minTimeStep;
	double _residualSleep;

	double _estimate = 5e-3f;
	double _mean = 5e-3f;
	double _m2 = 0.f;
	int64_t _count = 1;

public:
	SleepTimer(double timeStep);

	void startLoop();
	void endLoop();

private:
	void preciseSleep(double duration);
};
