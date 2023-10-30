#include "Application.hpp"
#include "GLFWApplicationImpl.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "LogManager.hpp"
#include "assets/AssetManager.hpp"
#include "assets/SystemGroupAsset.hpp"
#include "assets/GeneralSettingsAsset.hpp"
#include "assets/SceneAsset.hpp"
#include <thread>

int main()
{
	AssetManager::getInstance().init("settings.dat");

	auto generalSettings = AssetManager::getInstance().getAsset<GeneralSettingsAsset>("config");
	const GeneralSettings& settings = generalSettings->getSettings();
	const float minTimeStep = 1.f / settings.frameFrequence;

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
	float lastFrame = 0.0f;
	while (!window->isDone())
	{
		window->handle();

		float currentFrame = static_cast<float>(app.GetTime());
		float deltaTime = currentFrame - lastFrame;
		const float excessTime = glm::max(minTimeStep - deltaTime, 0.f);

		lastFrame = currentFrame + excessTime;

		world->update(deltaTime + excessTime);

		if (excessTime > 0.f) {
			const std::chrono::duration<float, std::chrono::seconds::period> duration(excessTime);
			std::this_thread::sleep_for(duration);
		}
	}

	world->deinit();

	return 0;
}
