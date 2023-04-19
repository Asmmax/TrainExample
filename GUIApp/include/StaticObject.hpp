#pragma once
#include "AGameObject.h"

#include <memory>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class StaticObject : public GameObject
{
public:
	StaticObject();
	StaticObject(const SharedMeshPtr& mesh);

	virtual void interpolate(float value) override {}
	virtual void init() override;
	virtual void update(float delta_time) override {}
	virtual void fixedUpdate(float fixed_time) override {}
};
