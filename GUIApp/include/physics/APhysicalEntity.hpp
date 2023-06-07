#pragma once
#include <memory>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform;

class PhysicalEntity
{
private:
	glm::vec3 _prev_position = glm::vec3(0.0f);
	glm::quat _prev_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 _prev_scale = glm::vec3(1.0f);

	glm::vec3 _next_position = glm::vec3(0.0f);
	glm::quat _next_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 _next_scale = glm::vec3(1.0f);

protected:
	std::shared_ptr<Transform> _transform;

public:
	virtual ~PhysicalEntity() = default;

	virtual void fixedUpdate(float fixed_time) = 0;

	void setTransform(const std::shared_ptr<Transform>& transform);
	void setNextPosition(const glm::vec3& position);
	void setNextRotation(const glm::vec3& rotation);
	void setNextRotation(const glm::quat& rotation);
	void setNextScale(const glm::vec3& scale);

	void resetPosition(const glm::vec3& position);
	void resetRotation(const glm::vec3& rotation);
	void resetRotation(const glm::quat& rotation);
	void resetScale(const glm::vec3& scale);

	void interpolate(float value);
};
