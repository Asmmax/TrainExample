#pragma once
#include "AComponent.hpp"
#include <glm/vec3.hpp>
#include <memory>

class RenderPointLight;

class LightComponent : public Component
{
private:
	std::shared_ptr<RenderPointLight> _light;

	float _radius;
	float _fadingArea;
	float _intensity;
	glm::vec3 _color;

public:
	LightComponent();

	void init() override;

	void setRadius(float radius);
	void setFadingArea(float fadingArea);
	void setIntensity(float intensity);
	void setColor(const glm::vec3& color);
};
