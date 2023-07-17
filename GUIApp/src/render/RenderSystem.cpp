#include "render/RenderSystem.hpp"
#include "render/CameraView.hpp"
#include "render/RenderObject.hpp"
#include "render/RenderPointLight.hpp"
#include "Model.hpp"

RenderSystem::RenderSystem():
	_window(nullptr),
	_mainCamera(nullptr),
	_model(std::make_shared<Model>())
{

}

void RenderSystem::init()
{
}

void RenderSystem::postUpdate(float delta_time)
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

void RenderSystem::setWindow(Window* window)
{
	_window = window;
}

std::shared_ptr<CameraView> RenderSystem::createCameraView(const std::shared_ptr<Transform>& transform)
{
	auto newCamera = std::make_shared<CameraView>(transform);
	newCamera->init(_window);
	_cameras.push_back(newCamera);
	return newCamera;
}

void RenderSystem::removeCameraView(const CameraViewPtr& view)
{
	auto foundIt = std::find(_cameras.begin(), _cameras.end(), view);
	if (foundIt != _cameras.end()) {
		_cameras.erase(foundIt);
		return;
	}

	if (_mainCamera == view) {
		setMainView(nullptr);
		auto foundIt = std::find(_cameras.begin(), _cameras.end(), view);
		_cameras.erase(foundIt);
	}
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
	if (_mainCamera) {
		_mainCamera->setMain();
	}
}

std::shared_ptr<RenderObject> RenderSystem::createObject(const std::shared_ptr<MeshAsset>& mesh, const std::shared_ptr<MaterialAsset>& material, const std::shared_ptr<Transform>& transform)
{
	auto object = std::make_shared<RenderObject>(_model, mesh, material, transform);
	object->init();
	_objects.push_back(object);
	return object;
}

void RenderSystem::removeObject(const RenderObjectPtr& object)
{
	auto foundIt = std::find(_objects.begin(), _objects.end(), object);
	if (foundIt != _objects.end()) {
		object->deinit();
		_objects.erase(foundIt);
	}
}

std::shared_ptr<RenderPointLight> RenderSystem::createPointLight(float radius, float fadingArea, float intensity, const glm::vec3& color, const std::shared_ptr<Transform>& transform)
{
	auto light = std::make_shared<RenderPointLight>(_model, radius, fadingArea, intensity, color, transform);
	light->init();
	_pointLights.push_back(light);
	return light;
}

void RenderSystem::removePointLight(const RenderPointLightPtr& light)
{
	auto foundIt = std::find(_pointLights.begin(), _pointLights.end(), light);
	if (foundIt != _pointLights.end()) {
		light->deinit();
		_pointLights.erase(foundIt);
	}
}
