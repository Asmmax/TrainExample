#pragma once
#include "AComponent.hpp"
#include <glm/vec3.hpp>
#include <memory>

class RenderPointLight;

/// @serializable
class LightComponent : public ComponentCommon<LightComponent>
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
	void deinit() override;

	/// @inject
	void setRadius(float radius);
	/// @inject
	void setFadingArea(float fadingArea);
	/// @inject
	void setIntensity(float intensity);
	/// @inject
	void setColor(const glm::vec3& color);
};
