#include "events/EventListener.hpp"
#include "events/AEvent.hpp"

EventListener::~EventListener()
{
	clearSubscriptions();
}

void EventListener::clearSubscriptions()
{
	std::vector<AEvent*> tempEvents(_events);
	for (AEvent* e : tempEvents) {
		e->removeListener(this);
	}
}


void EventListener::subscribe(AEvent* e)
{
	_events.push_back(e);
}

void EventListener::unsubscribe(AEvent* e)
{
	auto lastIt = std::remove(_events.begin(), _events.end(), e);
	_events.erase(lastIt, _events.end());
}
