#include "TrainBuilder.hpp"
#include "Primitives.hpp"
#include "TrackedObject.hpp"
#include "components/RenderComponent.hpp"
#include "World.hpp"
#include "ACurve.hpp"
#include "components/LightComponent.hpp"
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

	std::reverse(_initial_params.begin(), _initial_params.end());
}

void TrainBuilder::Build(World* world, const std::shared_ptr<SharedMesh>& mesh, const std::shared_ptr<Material>& material)
{
	bool first = true;
	for (auto param : _initial_params) {
		auto movable_object = std::make_shared<TrackedObject>(_path, _velocity);
		movable_object->setParameter(param);

		auto graphics_object = std::make_shared<GameObject>();
		graphics_object->setPosition(glm::vec3(0.0f, 0.25f, 0.0f));
		graphics_object->setScale(glm::vec3(1.0f, 0.5f, _block_length));

		auto renderComp = graphics_object->addComponent<RenderComponent>();
		renderComp->setMesh(mesh);
		renderComp->setMaterial(material);

		world->AddGameObject(graphics_object);

		movable_object->attachChild(graphics_object);

		if (first) {
			auto projector_object = std::make_shared<GameObject>();
			projector_object->setPosition(glm::vec3{ 0.0f, 10.0f, -5.0f });
			auto light = projector_object->addComponent<LightComponent>();
			light->setRadius(10.0f);
			light->setFadingArea(10.0f);
			light->setColor(glm::vec3{ 1.0f, 1.0f, 0.0f });

			world->AddGameObject(projector_object);

			movable_object->attachChild(projector_object);
			first = false;
		}

		world->AddGameObject(movable_object);
	}
}
