#include "Application.hpp"
#include "GLFWApplicationImpl.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "LogManager.hpp"
#include "assets/AssetManager.hpp"
#include "assets/SystemGroupAsset.hpp"
#include "assets/GeneralSettingsAsset.hpp"
#include "assets/SceneAsset.hpp"
#include "timers/SleepTimer.hpp"

int main()
{
	AssetManager::getInstance().init("settings.dat");

	auto generalSettings = AssetManager::getInstance().getAsset<GeneralSettingsAsset>("config");
	const GraphicsSettings& graphicsSettings = generalSettings->getGraphicsSettings();
	const double minTimeStep = 1.0 / graphicsSettings.framerate;

	const LogSettings& logSettings = generalSettings->getLogSettings();
	LogManager::getInstance().init(logSettings.logDir, logSettings.logs);

	// initialization
	Application& app = Application::getInstance();
	app.bindImpl<GLFWApplicationImpl>();
	Window* window = app.getWindow(graphicsSettings.width, graphicsSettings.height, "Train Example");
	if (!window)
		return -1;

	window->setVSync(graphicsSettings.vsync);
	if (graphicsSettings.fullscreen) {
		window->setFullscreen(graphicsSettings.width, graphicsSettings.height, graphicsSettings.framerate);
	}

	AssetManager::getInstance().setLoader(window->getLoader());

	std::shared_ptr<World> world = std::make_shared<World>();

	auto systemsConfig = AssetManager::getInstance().getAsset<SystemGroupAsset>("config");
	systemsConfig->init(window);
	systemsConfig->attachTo(*world);

	auto scene = AssetManager::getInstance().cloneAsset<SceneAsset>("scenes/train_scene");
	scene->attachTo(*world);

	world->init();

	// main loop
	std::shared_ptr<BaseTimer> timer = graphicsSettings.vsync
		? std::make_shared<BaseTimer>(minTimeStep, graphicsSettings.storedFrameCount)
		: std::make_shared<SleepTimer>(minTimeStep, graphicsSettings.storedFrameCount);

	while (!window->isDone())
	{
		LOG_DEBUG_PUSH_EX("time", "Frame");
		timer->startLoop();

		const float deltaTime = static_cast<float>(timer->getNextTimeStep());
		LOG_DEBUG_EX("time", "Predicted time step = " + std::to_string(deltaTime));

		window->handle();
		world->update(deltaTime);
		world->render();

		timer->endLoop();

		window->swapBuffers();
		LOG_DEBUG_POP_EX("time");
	}

	world->deinit();

	return 0;
}
