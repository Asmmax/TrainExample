#include "Application.hpp"
#include "GLFWApplicationImpl.hpp"
#include "Window.hpp"
#include "Path.hpp"
#include "World.hpp"
#include "InputController.hpp"
#include "WorldContext.hpp"

#include "components/CameraComponent.hpp"
#include "components/CameraManipulator.hpp"
#include "ACurve.hpp"
#include "Spline.hpp"
#include "Primitives.hpp"
#include "TrainBuilder.hpp"
#include "Rails.hpp"
#include "Sleepers.hpp"
#include "Material.hpp"
#include "resources/ShaderData.hpp"
#include "components/RenderComponent.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "components/LightComponent.hpp"
#include "physics/PhysicalSystem.hpp"

void initWorld(World* world, Loader* loader, const Path& directory)
{
	//init systems
	world->addSystem<PhysicalSystem>(0.02f);

	//init MainLight
	auto sun_object = std::make_shared<GameObject>();
	sun_object->setPosition(glm::vec3{ 100.0f, 200.0f, 100.0f });
	auto mainLight = sun_object->addComponent<LightComponent>();
	mainLight->setRadius(1000.0f);
	mainLight->setIntensity(0.5f);
	world->AddGameObject(sun_object);

	//init camera
	auto mainCameraObject = std::make_shared<GameObject>();
	mainCameraObject->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	mainCameraObject->setRotation(glm::vec3(-45.0f, 90.0f, 0.0f));
	auto mainCamera = mainCameraObject->addComponent<CameraComponent>();
	mainCamera->getTransform()->setPosition(glm::vec3{ 0, 0, 25 });
	mainCameraObject->getTransform()->addChild(mainCamera->getTransform());
	auto manipulator = mainCameraObject->addComponent<CameraManipulator>();
	world->AddGameObject(mainCameraObject);

	mainCamera->addView(world->getMainCameraView());

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

	auto plane_object = std::make_shared<GameObject>();
	plane_object->setPosition(glm::vec3(0, -0.01f, 0));
	plane_object->setRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
	plane_object->setScale(glm::vec3(20.0f));

	auto planeGraphics = plane_object->addComponent<RenderComponent>();
	planeGraphics->setMesh(plane_mesh);
	planeGraphics->setMaterial(grass);

	world->AddGameObject(plane_object);

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

	auto rails = std::make_shared<GameObject>();
	world->AddGameObject(rails);

	auto rails_mesh = std::make_shared<Rails>(path, 0.1f, 0.5f, 400);
	rails_mesh->load(*loader);

	auto rails_object = std::make_shared<GameObject>();
	rails_object->setPosition(glm::vec3(0.0f, 0.01f, 0.0f));

	auto railsGraphics = rails_object->addComponent<RenderComponent>();
	railsGraphics->setMesh(rails_mesh);
	railsGraphics->setMaterial(metal);

	world->AddGameObject(rails_object);

	rails->attachChild(rails_object);

	auto sleepers_mesh = std::make_shared<Sleepers>(path, 0.1f, 1.0f, 0.5f);
	sleepers_mesh->load(*loader);
	auto sleepers_object = std::make_shared<GameObject>();

	auto sleepersGraphics = sleepers_object->addComponent<RenderComponent>();
	sleepersGraphics->setMesh(sleepers_mesh);
	sleepersGraphics->setMaterial(wood);

	world->AddGameObject(sleepers_object);

	rails->attachChild(sleepers_object);
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

	std::shared_ptr<InputController> controller = std::make_shared<InputController>();
	controller->setMouseCaptureWhilePressed();
	controller->bind(window);

	std::shared_ptr<World> world = std::make_shared<World>();
	WorldContext::getInstance().init(world, controller);

	initWorld(world.get(), window->getLoader(), path);

	world->init(window);

	// main loop
	float lastFrame = 0.0f;
	while (!window->isDone())
	{
		window->handle();

		float currentFrame = static_cast<float>(app.GetTime());
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		world->update(deltaTime);
		world->draw();
	}
	return 0;
}
