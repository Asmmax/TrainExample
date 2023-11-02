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
	const double minTimeStep = 1.0 / settings.framerate;

	LogManager::getInstance().init(settings.logDir);

	// initialization
	Application& app = Application::getInstance();
	app.bindImpl<GLFWApplicationImpl>();
	Window* window = app.getWindow(settings.width, settings.height, "Train Example");
	if (!window)
		return -1;

	window->setVSync(settings.vsync);
	if (settings.fullscreen) {
		window->setFullscreen(settings.width, settings.height, settings.framerate);
	}
	const int realFramerate = window->getFramerate();

	AssetManager::getInstance().setLoader(window->getLoader());

	std::shared_ptr<World> world = std::make_shared<World>();

	auto systemsConfig = AssetManager::getInstance().getAsset<SystemGroupAsset>("config");
	systemsConfig->init(window);
	systemsConfig->attachTo(*world);

	auto scene = AssetManager::getInstance().cloneAsset<SceneAsset>("scenes/train_scene");
	scene->attachTo(*world);

	world->init();

	// main loop
	SleepTimer timer(minTimeStep, realFramerate != settings.framerate || !settings.vsync);
	float lastFrame = 0.0f;
	while (!window->isDone())
	{
		LOG_DEBUG_PUSH("Frame");
		timer.startLoop();

		const float deltaTime = static_cast<float>(timer.getNextTimeStep());
		LOG_DEBUG("Predicted time step = " + std::to_string(deltaTime));

		window->handle();
		world->update(deltaTime);

		timer.endLoop();

		window->swapBuffers();
		LOG_DEBUG_POP();
	}

	world->deinit();

	return 0;
}
