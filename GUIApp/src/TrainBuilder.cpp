#include "TrainBuilder.hpp"
#include "Primitives.hpp"
#include "GameObject.hpp"
#include "components/TrackedComponent.hpp"
#include "components/RenderComponent.hpp"
#include "World.hpp"
#include "ACurve.hpp"
#include "components/LightComponent.hpp"
#include "components/TransformComponent.hpp"

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
		auto movable_object = world->createGameObject();
		auto movableTransform = movable_object->addComponent<TransformComponent>();
		auto physicsComp = movable_object->addComponent<TrackedComponent>();
		physicsComp->setPath(_path);
		physicsComp->setVelocity(_velocity);
		physicsComp->setParameter(param);

		auto graphics_object = world->createGameObject();
		auto graphicsTransform = graphics_object->addComponent<TransformComponent>();
		graphicsTransform->setPosition(glm::vec3(0.0f, 0.25f, 0.0f));
		graphicsTransform->setScale(glm::vec3(1.0f, 0.5f, _block_length));
		movableTransform->attachChild(graphicsTransform);

		auto renderComp = graphics_object->addComponent<RenderComponent>();
		renderComp->setMesh(mesh);
		renderComp->setMaterial(material);

		if (first) {
			auto projector_object = world->createGameObject();
			auto projectorTransform = projector_object->addComponent<TransformComponent>();
			projectorTransform->setPosition(glm::vec3{ 0.0f, 10.0f, -5.0f });
			movableTransform->attachChild(projectorTransform);
			auto light = projector_object->addComponent<LightComponent>();
			light->setRadius(10.0f);
			light->setFadingArea(10.0f);
			light->setColor(glm::vec3{ 1.0f, 1.0f, 0.0f });

			first = false;
		}
	}
}
