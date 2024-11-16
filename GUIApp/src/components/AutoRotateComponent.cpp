#include "components/AutoRotateComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "World.hpp"

AutoRotateComponent::AutoRotateComponent(float speed, const glm::vec3& axis):
	_speed(speed),
	_axis(axis)
{
}

void AutoRotateComponent::init()
{

}

void AutoRotateComponent::update(float delta_time)
{
    auto transformComp = getOwner()->getComponent<TransformComponent>();
    std::shared_ptr<Transform> transform = transformComp->getTransform();

    auto rot = glm::angleAxis(-glm::radians(_speed * delta_time), _axis);

    const auto prevRot = transform->getLocalRotation();
    transform->setRotation(prevRot * rot);
}

