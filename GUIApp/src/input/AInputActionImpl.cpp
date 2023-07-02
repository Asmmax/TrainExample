#include "input/AInputActionImpl.hpp"

void AInputActionImpl::bindToPressed(void* owner, const std::function<void()>& callback)
{
	auto result = _actionPressed.emplace(owner, std::vector<std::function<void()>>{ callback });
	if (!result.second) {
		result.first->second.push_back(callback);
	}
}

void AInputActionImpl::bindToReleased(void* owner, const std::function<void()>& callback)
{
	auto result = _actionReleased.emplace(owner, std::vector<std::function<void()>>{ callback });
	if (!result.second) {
		result.first->second.push_back(callback);
	}
}

void AInputActionImpl::unbindAllPressed(void* owner)
{
	auto foundIt = _actionPressed.find(owner);
	if (foundIt != _actionPressed.end()) {
		_actionPressed.erase(foundIt);
	}
}

void AInputActionImpl::unbindAllReleased(void* owner)
{
	auto foundIt = _actionReleased.find(owner);
	if (foundIt != _actionReleased.end()) {
		_actionReleased.erase(foundIt);
	}
}

void AInputActionImpl::broadcastPressed()
{
	for (auto& callbackGroup : _actionPressed) {
		for (auto& callback : callbackGroup.second) {
			callback();
		}
	}
}

void AInputActionImpl::broadcastReleased()
{
	for (auto& callbackGroup : _actionReleased) {
		for (auto& callback : callbackGroup.second) {
			callback();
		}
	}
}
