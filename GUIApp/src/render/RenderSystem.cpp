#include "render/RenderSystem.hpp"
#include "render/CameraView.hpp"
#include "render/RenderObject.hpp"
#include "render/RenderPointLight.hpp"
#include "Model.hpp"

RenderSystem::RenderSystem(Window* window):
	_window(window),
	_mainCamera(nullptr),
	_model(std::make_shared<Model>())
{

}

void RenderSystem::init()
{
	_mainCamera->init(_window);

	for (auto& camera : _cameras) {
		camera->init(_window);
	}
}

void RenderSystem::update(float delta_time)
{
	for (auto& light : _pointLights) {
		light->update();
	}

	for (auto& object : _objects) {
		object->update();
	}

	for (auto& camera : _cameras) {
		camera->update();
	}
	_mainCamera->update();

	for (auto& camera : _cameras) {
		camera->render(*_model);
	}
	_mainCamera->render(*_model);
}

void RenderSystem::draw()
{

}

std::shared_ptr<CameraView> RenderSystem::createCameraView(const std::shared_ptr<Transform>& transform)
{
	auto newCamera = std::make_shared<CameraView>(transform);
	_cameras.push_back(newCamera);
	return newCamera;
}

void RenderSystem::setMainView(const CameraViewPtr& view)
{
	if (_mainCamera == view) {
		return;
	}

	if (_mainCamera) {
		_mainCamera->setSlave();
		_cameras.push_back(_mainCamera);
	}
	auto foundIt = std::find(_cameras.begin(), _cameras.end(), view);
	if (foundIt != _cameras.end()) {
		_cameras.erase(foundIt);
	}
	_mainCamera = view;
	_mainCamera->setMain();
}

std::shared_ptr<RenderObject> RenderSystem::createObject(const std::shared_ptr<SharedMesh>& mesh, const std::shared_ptr<Material>& material, const std::shared_ptr<Transform>& transform)
{
	auto object = std::make_shared<RenderObject>(_model, mesh, material, transform);
	_objects.push_back(object);
	return object;
}

std::shared_ptr<RenderPointLight> RenderSystem::createPointLight(float radius, float fadingArea, float intensity, const glm::vec3& color, const std::shared_ptr<Transform>& transform)
{
	auto light = std::make_shared<RenderPointLight>(_model, radius, fadingArea, intensity, color, transform);
	_pointLights.push_back(light);
	return light;
}
