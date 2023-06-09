#include "Application.hpp"
#include "GLFWApplicationImpl.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "assets/AssetManager.hpp"
#include "assets/SystemGroupAsset.hpp"

#include "common/components/TransformComponent.hpp"
#include "render/components/CameraComponent.hpp"
#include "render/components/RenderComponent.hpp"
#include "render/components/LightComponent.hpp"
#include "components/CameraManipulator.hpp"
#include "resources/ShaderData.hpp"
#include "ACurve.hpp"
#include "TrainBuilder.hpp"
#include "assets/MeshAsset.hpp"
#include "assets/MaterialAsset.hpp"
#include "GameObject.hpp"
#include "common/Transform.hpp"

void initWorld(World* world, Loader* loader)
{
	//init MainLight
	auto sun_object = world->createGameObject();
	auto sunObjectTransform = sun_object->addComponent<TransformComponent>();
	sunObjectTransform->setPosition(glm::vec3{ 100.0f, 200.0f, 100.0f });
	auto mainLight = sun_object->addComponent<LightComponent>();
	mainLight->setRadius(1000.0f);
	mainLight->setIntensity(0.5f);

	//init camera
	auto mainCameraObject = world->createGameObject();
	auto mainCameraTransform = mainCameraObject->addComponent<TransformComponent>();
	mainCameraTransform->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	mainCameraTransform->setRotation(glm::vec3(-45.0f, 90.0f, 0.0f));

	auto eyeCameraObject = world->createGameObject();
	auto eyeCameraTransform = eyeCameraObject->addComponent<TransformComponent>();
	eyeCameraTransform->setPosition(glm::vec3{ 0, 0, 25 });
	mainCameraTransform->attachChild(eyeCameraTransform);
	auto mainCamera = eyeCameraObject->addComponent<CameraComponent>();
	mainCamera->setMain();

	auto manipulator = mainCameraObject->addComponent<CameraManipulator>();
	manipulator->setEye(eyeCameraObject);

	//load path
	auto path = AssetManager::getInstance().getAsset<ACurve>("curves/path");

	//load materials
	auto grass = AssetManager::getInstance().getAsset<MaterialAsset>("materials/grass");
	auto trainMat = AssetManager::getInstance().getAsset<MaterialAsset>("materials/train");
	auto metal = AssetManager::getInstance().getAsset<MaterialAsset>("materials/metal");
	auto wood = AssetManager::getInstance().getAsset<MaterialAsset>("materials/wood");

	//load meshes
	auto plane_mesh = AssetManager::getInstance().getAsset<MeshAsset>("meshes/plane");
	auto cube_mesh = AssetManager::getInstance().getAsset<MeshAsset>("meshes/cube");
	auto rails_mesh = AssetManager::getInstance().getAsset<MeshAsset>("meshes/rails");
	auto sleepers_mesh = AssetManager::getInstance().getAsset<MeshAsset>("meshes/sleepers");

	// create background objects
	auto plane_object = world->createGameObject();

	auto planeTransform = plane_object->addComponent<TransformComponent>();
	planeTransform->setPosition(glm::vec3(0, -0.01f, 0));
	planeTransform->setRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
	planeTransform->setScale(glm::vec3(20.0f));

	auto planeGraphics = plane_object->addComponent<RenderComponent>();
	planeGraphics->setMesh(plane_mesh);
	planeGraphics->setMaterial(grass);

	TrainBuilder train(path, 8, 2.0f);
	train.Build(world, cube_mesh, trainMat);

	//create railway
	auto rails = world->createGameObject();
	auto railsTranform = rails->addComponent<TransformComponent>();

	auto rails_object = world->createGameObject();
	auto railsObjTranform = rails_object->addComponent<TransformComponent>();
	railsObjTranform->setPosition(glm::vec3(0.0f, 0.01f, 0.0f));
	railsTranform->attachChild(railsObjTranform);

	auto railsGraphics = rails_object->addComponent<RenderComponent>();
	railsGraphics->setMesh(rails_mesh);
	railsGraphics->setMaterial(metal);

	auto sleepers_object = world->createGameObject();
	auto sleepersTranform = sleepers_object->addComponent<TransformComponent>();
	railsTranform->attachChild(sleepersTranform);

	auto sleepersGraphics = sleepers_object->addComponent<RenderComponent>();
	sleepersGraphics->setMesh(sleepers_mesh);
	sleepersGraphics->setMaterial(wood);
}

int main()
{
	// initialization
	Application& app = Application::getInstance();
	app.bindImpl<GLFWApplicationImpl>();
	Window* window = app.getWindow(1600, 900, "Train Example");
	if (!window)
		return -1;

	AssetManager::getInstance().init("settings.dat", window->getLoader());

	std::shared_ptr<World> world = std::make_shared<World>();

	auto systemsConfig = AssetManager::getInstance().getAsset<SystemGroupAsset>("config");
	systemsConfig->init(window);
	systemsConfig->attachTo(*world);

	initWorld(world.get(), window->getLoader());

	world->init();

	// main loop
	float lastFrame = 0.0f;
	while (!window->isDone())
	{
		window->handle();

		float currentFrame = static_cast<float>(app.GetTime());
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		world->update(deltaTime);
	}
	return 0;
}
