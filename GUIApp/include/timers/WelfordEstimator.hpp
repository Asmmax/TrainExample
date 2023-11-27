#pragma once
#include <cstddef>

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
	double getMin() const;
	double getMax() const;
	double getStdMin() const;
	double getStdMax() const;

private:
	void init(double value);
};
