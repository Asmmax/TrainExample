#include "timers/QueueAverager.hpp"
#include <glm/glm.hpp>

QueueAverager::QueueAverager(size_t size):
	_mean(0.0),
	_size(size)
{
}

void QueueAverager::addPoint(double observed)
{
	if (_values.size() == 0) {
		init(observed);
		return;
	}

	_mean += (observed - _values.front()) / _size;

	_values.pop();
	_values.push(observed);
}

void QueueAverager::reset()
{
	while (_values.size() > 0) {
		_values.pop();
	}
}

void QueueAverager::init(double value)
{
	_mean = value;
	for (size_t i = 0; i < _size; i++) {
		_values.push(value);
	}
}
