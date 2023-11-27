#pragma once
#include "AComponent.hpp"
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>

class Transform;

class TransformComponent : public ComponentCommon<TransformComponent>
{
	using Ptr = std::shared_ptr<TransformComponent>;
private:
	std::shared_ptr<Transform> _transform;
	std::vector<Ptr> _pendingChildren;
	bool _isInited;

public:
	TransformComponent(const std::vector<Ptr>& children = std::vector<Ptr>());

	void init() override;
	void deinit() override;

	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& rotation);
	void setRotation(const glm::quat& rotation);
	void setScale(const glm::vec3& scale);

	void attachChild(const std::shared_ptr<TransformComponent>& child);
	const std::shared_ptr<Transform>& getTransform() { return _transform; }

private:
	void applyAttachChild();
};
