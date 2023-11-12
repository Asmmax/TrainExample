#include "timers/QueueEstimator.hpp"
#include <glm/glm.hpp>

QueueEstimator::QueueEstimator(size_t size):
	_mean(0.0),
	_m2(0.0),
	_stddev(0.0),
	_size(size)
{
}

void QueueEstimator::addPoint(double observed)
{
	if (_values.size() == 0) {
		init(observed);
		return;
	}

	const double dev = _values.back() - _mean;
	_m2 -= dev * dev;
	_mean += (observed - _values.back()) / _size;
	const double newDev = observed - _mean;
	_m2 += newDev * newDev;
	_stddev = glm::sqrt(_m2 / (_size - 1));

	_values.pop();
	_values.push(observed);
}

void QueueEstimator::reset() 
{
	while (_values.size() > 0) {
		_values.pop();
	}
}

void QueueEstimator::init(double value)
{
	_mean = value;
	_stddev = 0.0;
	_m2 = 0;
	for (size_t i = 0; i < _size; i++) {
		_values.push(value);
	}
}
