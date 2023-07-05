#include "input/AInputActionImpl.hpp"

void AInputActionImpl::bindToPressed(EventListener* owner, const Event<>::Callback& callback)
{
	_actionPressed.bind(owner, callback);
}

void AInputActionImpl::bindToReleased(EventListener* owner, const Event<>::Callback& callback)
{
	_actionReleased.bind(owner, callback);
}

void AInputActionImpl::unbindAllPressed(EventListener* owner)
{
	_actionPressed.unbindAll(owner);
}

void AInputActionImpl::unbindAllReleased(EventListener* owner)
{
	_actionReleased.unbindAll(owner);
}
