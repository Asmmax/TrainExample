#include "components/LightComponent.hpp"
#include "WorldContext.hpp"
#include "World.hpp"
#include "Model.hpp"
#include "objects/Light.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

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
	_model = WorldContext::getInstance().getWorld()->getModel();
	_light = _model->createLight();
	_light->setRadius(_radius);
	_light->setFadingArea(_fadingArea);
	_light->setIntensity(_intensity);
	_light->setColor(_color);
}

void LightComponent::predraw() 
{
	if (!_light) {
		return;
	}

	auto transform = getOwner()->getTransform();
	if (!transform) {
		return;
	}

	auto& position = transform->getGlobalPosition();
	_light->setPosition(position);
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
