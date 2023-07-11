#include "components/FlyCameraManipulator.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"

FlyCameraManipulator::FlyCameraManipulator(float rotSpeed, float speed, float speedUpCoef):
	RotateCameraManipulator(rotSpeed),
	_speed(speed),
	_speedUpCoef(speedUpCoef)
{
}

void FlyCameraManipulator::move(const glm::vec3& direction)
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();

	float speed = _speed;
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (inputSystem && inputSystem->isActionPressed("SpeedUp")) {
		speed *= _speedUpCoef;
	}

	std::shared_ptr<Transform> target = transformComp->getTransform();
	auto position = target->getLocalPosition();
	transformComp->setPosition(position + speed *direction);
}
