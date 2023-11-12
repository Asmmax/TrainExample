#pragma once
#include <queue>

class QueueEstimator
{
private:
	std::queue<double> _values;
	double _mean;
	double _m2;
	double _stddev;
	size_t _size;

public:
	QueueEstimator(size_t size);

	void addPoint(double observed);
	void reset();
	double getMean() const { return _mean; }
	double getDeviation() const { return _stddev; }

private:
	void init(double value);
};
