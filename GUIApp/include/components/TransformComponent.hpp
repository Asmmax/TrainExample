#pragma once
#include "components/AComponent.hpp"
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>

class Transform;

class TransformComponent : public Component
{
private:
	std::shared_ptr<Transform> _transform;

public:
	TransformComponent();

	void init() override;

	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& rotation);
	void setRotation(const glm::quat& rotation);
	void setScale(const glm::vec3& scale);

	void attachChild(const std::shared_ptr<TransformComponent>& child);
	const std::shared_ptr<Transform>& getTransform() { return _transform; }
};