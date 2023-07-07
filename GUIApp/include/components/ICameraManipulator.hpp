#pragma once
#include <memory>
#include <glm/glm.hpp>

class Transform;

/// @serializable @abstract @shared
class ICameraManipulator
{
public:
	virtual ~ICameraManipulator() = default;

	virtual void rotate(float stepX, float stepY) = 0;
	virtual void move(const glm::vec3& direction) = 0;
	virtual void zoom(float step) = 0;
	virtual std::shared_ptr<Transform> getTransform() = 0;

	virtual void apply() = 0;
};
