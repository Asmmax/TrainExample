#pragma once
#include <vector>

class AEvent;

class EventListener
{
	friend class AEvent;
	std::vector<AEvent*> _events;

public:
	~EventListener();

	void clearSubscriptions();

private:
	void subscribe(AEvent* e);
	void unsubscribe(AEvent* e);
};
