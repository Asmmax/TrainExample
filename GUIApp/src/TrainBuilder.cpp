#include "TrainBuilder.hpp"
#include "Primitives.hpp"
#include "TrackedObject.hpp"
#include "World.hpp"
#include "ACurve.hpp"
#include <memory>

TrainBuilder::TrainBuilder(const std::shared_ptr<ACurve>& path, unsigned int block_count, float velocity, float block_length, float gap):
	_path(path),
	_velocity(velocity),
	_block_length(block_length),
	_block_count(block_count)
{
	float step = block_length + gap;

	_initial_params.reserve(block_count);

	float parameter = 0.0f;
	_initial_params.push_back(parameter);

	for (unsigned int i = 1; i < block_count; i++) {
		parameter = path->getNextParamByStep(parameter, step);
		_initial_params.push_back(parameter);
	}
}

void TrainBuilder::Build(World* world)
{
	auto cube_mesh = std::make_shared<Cube>();

	for (auto param : _initial_params) {
		auto movable_object = std::make_shared<TrackedObject>(cube_mesh, _path, _velocity);
		movable_object->setParameter(param);
		movable_object->setColor(0.62f, 0.58f, 0.51f);
		movable_object->setScale(glm::vec3(1.0f, 0.5f, _block_length));
		movable_object->setOffset(glm::vec3(0.0f, 0.25f, 0.0f));
		world->AddGameObject(movable_object);
	}
}
