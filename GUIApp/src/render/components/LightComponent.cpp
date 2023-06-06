#include "render/components/LightComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "World.hpp"
#include "GameObject.hpp"
#include "render/RenderSystem.hpp"
#include "render/RenderPointLight.hpp"

LightComponent::LightComponent():
	_light(nullptr),
	_radius(100.0f),
	_fadingArea(0.0f),
	_intensity(1.0f),
	_color(1.0f)
{
}

void LightComponent::init() 
{
	auto renderSystem = getOwner()->getWorld()->getSystem<RenderSystem>();
	if (!renderSystem) {
		return;
	}

	auto transformComp = getOwner()->getComponent<TransformComponent>();
	_light = renderSystem->createPointLight(_radius, _fadingArea, _intensity, _color, transformComp->getTransform());
}

void LightComponent::setRadius(float radius)
{
	_radius = radius;

	if (_light) {
		_light->setRadius(_radius);
	}
}

void LightComponent::setFadingArea(float fadingArea)
{
	_fadingArea = fadingArea;

	if (_light) {
		_light->setFadingArea(_fadingArea);
	}
}

void LightComponent::setIntensity(float intensity)
{
	_intensity = intensity;

	if (_light) {
		_light->setIntensity(_intensity);
	}
}

void LightComponent::setColor(const glm::vec3& color)
{
	_color = color;

	if (_light) {
		_light->setColor(_color);
	}
}
