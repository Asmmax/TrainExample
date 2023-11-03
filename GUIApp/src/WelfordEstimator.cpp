#include "WelfordEstimator.hpp"
#include <glm/glm.hpp>

WelfordEstimator::WelfordEstimator() :
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
	_stddev = glm::sqrt(_m2 / (_count - 1));
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

double WelfordEstimator::getMin() const
{
	return getMean() - 3 * getDeviation();
}

double WelfordEstimator::getMax() const
{
	return getMean() + 3 * getDeviation();
}

double WelfordEstimator::getStdMin() const
{
	return getMean() - getDeviation();
}

double WelfordEstimator::getStdMax() const
{
	return getMean() + getDeviation();
}
