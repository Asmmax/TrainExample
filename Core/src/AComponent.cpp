#include "AComponent.hpp"
#include <assert.h>

void Component::deinit()
{
	clearSubscriptions();
}

GameObject* Component::getOwner()
{ 
	assert(_owner);
	return _owner; 
}

const GameObject* Component::getOwner() const
{ 
	assert(_owner);
	return _owner; 
}

void Component::setOwner(GameObject* owner)
{
	_owner = owner;
}
