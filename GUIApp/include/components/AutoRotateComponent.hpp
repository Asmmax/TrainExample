#pragma once
#include "ComponentCommon.hpp"
#include <string>
#include <list>
#include <glm/glm.hpp>

class GameObject;

class AutoRotateComponent : public ComponentCommon<AutoRotateComponent>
{
private:
	float _speed;
	glm::vec3 _axis;

public:
	AutoRotateComponent(float speed, const glm::vec3& axis);

	void init() override;
	void update(float delta_time) override;
};
