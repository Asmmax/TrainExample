#include "Application.hpp"
#include "GLFWApplicationImpl.hpp"
#include "Window.hpp"
#include "Path.hpp"
#include "World.hpp"

#include "input/InputSystem.hpp"
#include "physics/PhysicalSystem.hpp"
#include "common/TransformSystem.hpp"
#include "render/RenderSystem.hpp"

#include "components/CameraComponent.hpp"
#include "components/CameraManipulator.hpp"
#include "components/RenderComponent.hpp"
#include "components/LightComponent.hpp"
#include "components/TransformComponent.hpp"
#include "resources/ShaderData.hpp"
#include "ACurve.hpp"
#include "Spline.hpp"
#include "Primitives.hpp"
#include "TrainBuilder.hpp"
#include "Rails.hpp"
#include "Sleepers.hpp"
#include "Material.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

void initSystems(World* world, Window* window) 
{
	auto inputSystem = world->addSystem<InputSystem>(window);
	inputSystem->setMouseCaptureWhilePressed();
	world->addSystem<PhysicalSystem>(0.02f);
	world->addSystem<TransformSystem>();
	world->addSystem<RenderSystem>(window);
}

void initWorld(World* world, Loader* loader, const Path& directory)
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

	//init curve
	std::vector<glm::vec3> points;
	points.reserve(8);
	points.emplace_back(0.0f, 0.5f, 7.0f); // 1
	points.emplace_back(-6.0f, 0.5f, 5.0f); // 2
	points.emplace_back(-8.0f, 0.5f, 1.0f); // 3
	points.emplace_back(-4.0f, 4.5f, -6.0f); // 4
	points.emplace_back(0.0f, 0.5f, -7.0f); // 5
	points.emplace_back(1.0f, 0.5f, -4.0f); // 6
	points.emplace_back(4.0f, 0.5f, -3.0f); // 7
	points.emplace_back(8.0f, 0.5f, 7.0f); // 8
	std::shared_ptr<ACurve> path = std::make_shared<Spline>(points, true);

	//load shaders
	std::string vertexShader = loadShader(directory.find("shaders/simple.vert"));
	std::string fragmentShader = loadShader(directory.find("shaders/simple.frag"));

	// create background objects
	auto grass = std::make_shared<Material>();
	grass->setVertexShader(vertexShader);
	grass->setFragmentShader(fragmentShader);
	grass->setColor(0.2f, 0.37f, 0.2f);
	grass->loadShader(*loader);

	auto plane_mesh = std::make_shared<Plane>();
	plane_mesh->load(*loader);

	auto plane_object = world->createGameObject();

	auto planeTransform = plane_object->addComponent<TransformComponent>();
	planeTransform->setPosition(glm::vec3(0, -0.01f, 0));
	planeTransform->setRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
	planeTransform->setScale(glm::vec3(20.0f));

	auto planeGraphics = plane_object->addComponent<RenderComponent>();
	planeGraphics->setMesh(plane_mesh);
	planeGraphics->setMaterial(grass);

	//create movable object
	auto trainMat = std::make_shared<Material>();
	trainMat->setVertexShader(vertexShader);
	trainMat->setFragmentShader(fragmentShader);
	trainMat->setColor(0.62f, 0.58f, 0.51f);
	trainMat->loadShader(*loader);

	auto cube_mesh = std::make_shared<Cube>();
	cube_mesh->load(*loader);
	TrainBuilder train(path, 8, 2.0f);
	train.Build(world, cube_mesh, trainMat);

	//create railway
	auto metal = std::make_shared<Material>();
	metal->setVertexShader(vertexShader);
	metal->setFragmentShader(fragmentShader);
	metal->setColor(0.25f, 0.25f, 0.25f);
	metal->loadShader(*loader);

	auto wood = std::make_shared<Material>();
	wood->setVertexShader(vertexShader);
	wood->setFragmentShader(fragmentShader);
	wood->setColor(0.5f, 0.25f, 0.0f);
	wood->loadShader(*loader);

	auto rails = world->createGameObject();
	auto railsTranform = rails->addComponent<TransformComponent>();

	auto rails_mesh = std::make_shared<Rails>(path, 0.1f, 0.5f, 400);
	rails_mesh->load(*loader);

	auto rails_object = world->createGameObject();
	auto railsObjTranform = rails_object->addComponent<TransformComponent>();
	railsObjTranform->setPosition(glm::vec3(0.0f, 0.01f, 0.0f));
	railsTranform->attachChild(railsObjTranform);

	auto railsGraphics = rails_object->addComponent<RenderComponent>();
	railsGraphics->setMesh(rails_mesh);
	railsGraphics->setMaterial(metal);

	auto sleepers_mesh = std::make_shared<Sleepers>(path, 0.1f, 1.0f, 0.5f);
	sleepers_mesh->load(*loader);

	auto sleepers_object = world->createGameObject();
	auto sleepersTranform = sleepers_object->addComponent<TransformComponent>();
	railsTranform->attachChild(sleepersTranform);

	auto sleepersGraphics = sleepers_object->addComponent<RenderComponent>();
	sleepersGraphics->setMesh(sleepers_mesh);
	sleepersGraphics->setMaterial(wood);
}

int main()
{
	Path path("settings.dat");

	// initialization
	Application& app = Application::getInstance();
	app.bindImpl<GLFWApplicationImpl>();
	Window* window = app.getWindow(1600, 900, "Train Example");
	if (!window)
		return -1;

	std::shared_ptr<World> world = std::make_shared<World>();

	initSystems(world.get(), window);
	initWorld(world.get(), window->getLoader(), path);

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
