#include "Application.hpp"
#include "GLFWApplicationImpl.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "LogManager.hpp"
#include "assets/AssetManager.hpp"
#include "assets/SystemGroupAsset.hpp"
#include "assets/GeneralSettingsAsset.hpp"
#include "assets/SceneAsset.hpp"
#include "SleepTimer.hpp"

int main()
{
	AssetManager::getInstance().init("settings.dat");

	auto generalSettings = AssetManager::getInstance().getAsset<GeneralSettingsAsset>("config");
	const GeneralSettings& settings = generalSettings->getSettings();
	const double minTimeStep = 1.0 / settings.frameFrequence;

	LogManager::getInstance().init(settings.logDir);

	// initialization
	Application& app = Application::getInstance();
	app.bindImpl<GLFWApplicationImpl>();
	Window* window = settings.fullscreen ? app.getFullscreenWindow("Train Example") : app.getWindow(1600, 900, "Train Example");
	if (!window)
		return -1;

	AssetManager::getInstance().setLoader(window->getLoader());

	std::shared_ptr<World> world = std::make_shared<World>();

	auto systemsConfig = AssetManager::getInstance().getAsset<SystemGroupAsset>("config");
	systemsConfig->init(window);
	systemsConfig->attachTo(*world);

	auto scene = AssetManager::getInstance().cloneAsset<SceneAsset>("scenes/train_scene");
	scene->attachTo(*world);

	world->init();

	// main loop
	SleepTimer timer(minTimeStep);
	float lastFrame = 0.0f;
	while (!window->isDone())
	{
		timer.startLoop();

		const float currentFrame = static_cast<float>(app.GetTime());
		const float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window->handle();
		world->update(deltaTime);

		timer.endLoop();
	}

	world->deinit();

	return 0;
}
