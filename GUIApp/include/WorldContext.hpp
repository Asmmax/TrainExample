#pragma once
#include <memory>

class World;
class InputController;

class WorldContext
{
private:
	std::shared_ptr<World> _world;
	std::shared_ptr<InputController> _input;

public:
	static WorldContext& getInstance();

	void init(const std::shared_ptr<World>& world, const std::shared_ptr<InputController>& input);

	const std::shared_ptr<World>& getWorld() { return _world; }
	const std::shared_ptr<InputController>& getInput() { return _input; }

private:
	WorldContext() = default;
};
