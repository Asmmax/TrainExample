#include "components/AComponent.hpp"
#include <assert.h>

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
