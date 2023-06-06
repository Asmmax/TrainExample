#include "render/RenderPointLight.hpp"
#include "Model.hpp"
#include "objects/Light.hpp"
#include "Transform.hpp"

RenderPointLight::RenderPointLight(const std::shared_ptr<Model>& model, float radius, float fadingArea, float intensity, const glm::vec3& color, const std::shared_ptr<Transform>& transform):
	_model(model),
	_radius(radius),
	_fadingArea(fadingArea),
	_intensity(intensity),
	_color(color),
	_transform(transform),
	_light(nullptr)
{
	_light = _model->createLight();
	_light->setRadius(_radius);
	_light->setFadingArea(_fadingArea);
	_light->setIntensity(_intensity);
	_light->setColor(_color);
}

void RenderPointLight::update()
{
	if (!_light) {
		return;
	}

	if (!_transform) {
		return;
	}

	auto& position = _transform->getGlobalPosition();
	_light->setPosition(position);
}

void RenderPointLight::setRadius(float radius)
{
	_radius = radius;

	if (_light) {
		_light->setRadius(_radius);
	}
}

void RenderPointLight::setFadingArea(float fadingArea)
{
	_fadingArea = fadingArea;

	if (_light) {
		_light->setFadingArea(_fadingArea);
	}
}

void RenderPointLight::setIntensity(float intensity)
{
	_intensity = intensity;

	if (_light) {
		_light->setIntensity(_intensity);
	}
}

void RenderPointLight::setColor(const glm::vec3& color)
{
	_color = color;

	if (_light) {
		_light->setColor(_color);
	}
}
