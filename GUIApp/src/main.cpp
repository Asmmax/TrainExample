#include "Application.hpp"
#include "Path.hpp"
#include "World.hpp"

int main()
{
	Path path("settings.dat");

	// initialization
	Engine *engine = Engine::get();
	engine->init(1600, 900, "UNIGINE Test Task");

	// set up camera
	Camera &cam = engine->getCamera();
	cam.Position = vec3(0.0f, 12.0f, 17.0f);
	cam.Yaw = -90.0f;
	cam.Pitch = -45.0f;
	cam.UpdateCameraVectors();

	World world(0.02f);
	world.init();

	// main loop
	while (!engine->isDone())
	{
		engine->update();
		world.update(engine->getDeltaTime());

		engine->render();
		world.draw();
		
		engine->swap();
	}

	engine->shutdown();
	return 0;
}
