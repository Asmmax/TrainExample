#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>

class EventListener;

class AEvent
{
private:
	std::vector<EventListener*> _listeners;

public:
	virtual ~AEvent();

	void addListener(EventListener* listener);
	void removeListener(EventListener* listener);

protected:
	virtual void listenerRemoved(EventListener* listener) = 0;
};

template <typename ...Args>
class Event : public AEvent
{
public:
	using Callback = std::function<void(Args...)>;

private:
	std::unordered_map<EventListener*, std::vector<Callback>> _callbacks;

public:
	void bind(EventListener* owner, const Callback& callback);
	void unbindAll(EventListener* owner);

	void broadcast(const Args&... args);

protected:
	void listenerRemoved(EventListener* listener) override;
};

template <typename ...Args>
void Event<Args...>::bind(EventListener* owner, const Callback& callback)
{
	addListener(owner);
	auto result = _callbacks.emplace(owner, std::vector<Callback>{ callback });
	if (!result.second) {
		result.first->second.push_back(callback);
	}
}

template <typename ...Args>
void Event<Args...>::unbindAll(EventListener* owner)
{
	removeListener(owner);
}

template <typename ...Args>
void Event<Args...>::broadcast(const Args&... args)
{
	for (auto& pair : _callbacks) {
		for (auto& callback : pair.second) {
			callback(args...);
		}
	}
}

template <typename ...Args>
void Event<Args...>::listenerRemoved(EventListener* listener)
{
	auto foundIt = _callbacks.find(listener);
	if (foundIt != _callbacks.end()) {
		_callbacks.erase(foundIt);
	}
}
