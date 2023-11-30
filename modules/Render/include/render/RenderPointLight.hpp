#pragma once
#include <glm/vec3.hpp>
#include <memory>

class Model;
class Light;
class Transform;

class RenderPointLight
{
private:
	std::shared_ptr<Model> _model;

	float _radius;
	float _fadingArea;
	float _intensity;
	glm::vec3 _color;
	std::shared_ptr<Transform> _transform;
	Light* _light;

public:
	RenderPointLight(const std::shared_ptr<Model>& model, float radius, float fadingArea, float intensity, const glm::vec3& color, const std::shared_ptr<Transform>& transform);

	void init();
	void deinit();
	void update();

	void setRadius(float radius);
	void setFadingArea(float fadingArea);
	void setIntensity(float intensity);
	void setColor(const glm::vec3& color);
};
