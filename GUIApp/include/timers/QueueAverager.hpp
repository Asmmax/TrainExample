#pragma once
#include <queue>

class QueueAverager
{
private:
	std::queue<double> _values;
	double _mean;
	size_t _size;

public:
	QueueAverager(size_t size);

	void addPoint(double observed);
	void reset();
	double getMean() const { return _mean; }

private:
	void init(double value);
};
