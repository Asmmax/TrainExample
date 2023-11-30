#pragma once
#include "events/AEvent.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

class InputDistributor;

class AInputActionImpl
{
protected:
	Event<> _actionPressed;
	Event<> _actionReleased;

public:
	virtual ~AInputActionImpl() = default;

	virtual void init(InputDistributor* distributor) = 0;
	virtual bool isPressed() const = 0;

	void bindToPressed(EventListener* owner, const Event<>::Callback& callback);
	void bindToReleased(EventListener* owner, const Event<>::Callback& callback);
	void unbindAllPressed(EventListener* owner);
	void unbindAllReleased(EventListener* owner);
};
