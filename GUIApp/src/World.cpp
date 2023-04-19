#include "World.hpp"
#include "StaticObject.hpp"
#include "Circle2D.hpp"
#include "Primitives.hpp"
#include "Rails.hpp"
#include "Sleepers.hpp"
#include "TrainBuilder.hpp"
#include "Spline.hpp"
#include "framework/utils.h"


World::World(float fixed_time):
	_fixed_time(fixed_time)
{
	//init curve
	std::vector<glm::vec3> points;
	points.reserve(8);
	points.emplace_back(0.0f, 0.f, 7.0f); // 1
	points.emplace_back(-6.0f, 0.f, 5.0f); // 2
	points.emplace_back(-8.0f, 0.f, 1.0f); // 3
	points.emplace_back(-4.0f, 0.f, -6.0f); // 4
	points.emplace_back(0.0f, 0.f, -7.0f); // 5
	points.emplace_back(1.0f, 0.f, -4.0f); // 6
	points.emplace_back(4.0f, 0.f, -3.0f); // 7
	points.emplace_back(8.0f, 0.f, 7.0f); // 8
	_path = std::make_shared<Spline>(points, true);

	// create background objects
	auto plane_mesh = std::make_shared<Plane>();
	auto plane_object = std::make_shared<StaticObject>(plane_mesh);
	plane_object->setColor(0.2f, 0.37f, 0.2f);
	plane_object->setPosition(glm::vec3(0, -0.01f, 0));
	plane_object->setRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
	plane_object->setScale(glm::vec3(20.0f));
	AddGameObject(plane_object);

	//create movable object
	TrainBuilder train(_path, 8, 2.0f);
	train.Build(this);

	//create railway
	auto rails_mesh = std::make_shared<Rails>(_path, 0.1f, 0.5f, 400);
	auto rails_object = std::make_shared<StaticObject>(rails_mesh);
	rails_object->setColor(0.25f, 0.25f, 0.25f);
	rails_object->setOffset(glm::vec3(0.0f, 0.01f, 0.0f));
	AddGameObject(rails_object);

	auto sleepers_mesh = std::make_shared<Sleepers>(_path, 0.1f, 1.0f, 0.5f);
	auto sleepers_object = std::make_shared<StaticObject>(sleepers_mesh);
	sleepers_object->setColor(0.5f, 0.25f, 0.0f);
	AddGameObject(sleepers_object);
}

World::~World() = default;

void World::AddGameObject(const GameObjectPtr& game_object)
{
	_game_objects.push_back(game_object);
}

void World::init()
{
	for (auto& game_object : _game_objects) {
		game_object->init();
	}
}

void World::draw()
{
#ifdef _DEBUG
	if (_path) {
		_path->draw(100);
	}
#endif
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
		game_object->update(delta_time);
	}
}

void World::fixedUpdate()
{
	for (auto& game_object : _game_objects) {
		game_object->fixedUpdate(_fixed_time);
	}
}
