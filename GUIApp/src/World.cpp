#include "World.hpp"
#include "GameObject.hpp"
#include "APlayerController.hpp"
#include "CameraView.hpp"
#include "MainCameraView.hpp"
#include "Transform.hpp"
#include "Model.hpp"

World::World(float fixed_time):
	_fixed_time(fixed_time),
	_time_redundant(0.0f),
	_isInited(false),
	_window(nullptr),
	_mainCamera(std::make_shared<MainCameraView>()),
	_model(std::make_shared<Model>())
{
}

World::~World() = default;

void World::AddGameObject(const GameObjectPtr& game_object)
{
	_game_objects.push_back(game_object);
}

std::shared_ptr<ICameraView> World::getMainCameraView() const
{
	return _mainCamera;
}

std::shared_ptr<ICameraView> World::CreateCameraView(int width, int height)
{
	auto newCamera = std::make_shared<CameraView>(width, height);
	_cameras.push_back(newCamera);
	return newCamera;
}

void World::init(Window* window)
{
	for (auto& game_object : _game_objects) {
		game_object->init();
	}

	_mainCamera->init(window);

	for (auto& camera : _cameras) {
		camera->init(window);
	}

	_isInited = true;
}

void World::update(float delta_time)
{
	_time_redundant += delta_time;
	while (_time_redundant >= _fixed_time) {
		_time_redundant -= _fixed_time;
		fixedUpdate();
	}

	for (auto& game_object : _game_objects) {
		game_object->interpolate(_time_redundant / _fixed_time);
	}

	for (auto& game_object : _game_objects) {
		game_object->update(delta_time);
	}

	for (auto& game_object : _game_objects) {
		auto& transform = game_object->getTransform();
		if (!transform->getParent()) {
			transform->compute();
		}
	}

	for (auto& game_object : _game_objects) {
		game_object->predraw();
	}
}

void World::draw()
{
	for (auto& camera : _cameras) {
		camera->render(*_model);
	}
	_mainCamera->render(*_model);
}

void World::fixedUpdate()
{
	for (auto& game_object : _game_objects) {
		game_object->fixedUpdate(_fixed_time);
	}
}
