#pragma once
#include "AGameObject.h"

#include <memory>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class DynamicObject : public GameObject
{
public:
	DynamicObject();
	DynamicObject(const SharedMeshPtr& mesh);

	virtual void interpolate(float value) override;
	virtual void init() override;
	virtual void update(float delta_time) override {}
	virtual void fixedUpdate(float fixed_time) override {}

protected:
	void setNextPosition(const glm::vec3& position);
	void setNextRotation(const glm::vec3& rotation);
	void setNextRotation(const glm::quat& rotation);
	void setNextScale(const glm::vec3& scale);

private:
	glm::vec3 _next_position = glm::vec3(0.0f);
	glm::quat _next_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 _next_scale = glm::vec3(1.0f);
};
