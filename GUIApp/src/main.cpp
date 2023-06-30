#include "Application.hpp"
#include "GLFWApplicationImpl.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "assets/AssetManager.hpp"
#include "assets/SystemGroupAsset.hpp"
#include "assets/SceneAsset.hpp"

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

	auto scene = AssetManager::getInstance().cloneAsset<SceneAsset>("scenes/train_scene");
	scene->attachTo(*world);

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

	world->deinit();

	return 0;
}
