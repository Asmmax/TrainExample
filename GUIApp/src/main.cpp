#include "Application.hpp"
#include "GLFWApplicationImpl.hpp"
#include "Window.hpp"
#include "Path.hpp"
#include "World.hpp"
#include "InputController.hpp"

#include "Camera.hpp"
#include "CameraManipulator.hpp"
#include "ACurve.hpp"
#include "Spline.hpp"
#include "Primitives.hpp"
#include "TrainBuilder.hpp"
#include "Rails.hpp"
#include "Sleepers.hpp"
#include "Material.hpp"
#include "resources/ShaderData.hpp"

void initWorld(World* world, Loader* loader, const Path& directory)
{
	//init camera
	auto mainCamera = std::make_shared<Camera>();
	mainCamera->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	mainCamera->setRotation(glm::vec3(-45.0f, 90.0f, 0.0f));
	world->AddGameObject(mainCamera);

	mainCamera->addView(world->getMainCameraView());

	//init controller
	auto manipulator = std::make_shared<CameraManipulator>(mainCamera);
	world->AddPlayerController(manipulator);

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
	auto plane_object = std::make_shared<GameObject>(plane_mesh);
	plane_object->setMaterial(grass);
	plane_object->setPosition(glm::vec3(0, -0.01f, 0));
	plane_object->setRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
	plane_object->setScale(glm::vec3(20.0f));
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
	auto rails_object = std::make_shared<GameObject>(rails_mesh);
	rails_object->setMaterial(metal);
	rails_object->setPosition(glm::vec3(0.0f, 0.01f, 0.0f));
	world->AddGameObject(rails_object);

	rails->attachChild(rails_object);

	auto sleepers_mesh = std::make_shared<Sleepers>(path, 0.1f, 1.0f, 0.5f);
	sleepers_mesh->load(*loader);
	auto sleepers_object = std::make_shared<GameObject>(sleepers_mesh);
	sleepers_object->setMaterial(wood);
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
	controller->bind(window);

	World world(0.02f);
	initWorld(&world, window->getLoader(), path);

	world.init(window);
	world.setInput(controller);

	// main loop
	float lastFrame = 0.0f;
	while (!window->isDone())
	{
		window->handle();

		float currentFrame = static_cast<float>(app.GetTime());
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		world.update(deltaTime);
		world.draw();
	}
	return 0;
}
