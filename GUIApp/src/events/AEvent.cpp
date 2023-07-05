#include "events/AEvent.hpp"
#include "events/EventListener.hpp"

AEvent::~AEvent()
{
	std::vector<EventListener*> tempListeners(_listeners);
	for (EventListener* listener : tempListeners) {
		listener->unsubscribe(this);
	}
}

void AEvent::addListener(EventListener* listener)
{
	_listeners.push_back(listener);
	listener->subscribe(this);
}

void AEvent::removeListener(EventListener* listener)
{
	auto lastIt = std::remove(_listeners.begin(), _listeners.end(), listener);
	if (lastIt == _listeners.end()) {
		return;
	}

	_listeners.erase(lastIt, _listeners.end());
	listener->unsubscribe(this);
	listenerRemoved(listener);
}
