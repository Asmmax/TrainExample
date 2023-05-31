#include "WorldContext.hpp"

WorldContext& WorldContext::getInstance()
{
	static WorldContext instance;
	return instance;
}

void WorldContext::init(const std::shared_ptr<World>& world, const std::shared_ptr<InputController>& input)
{
	_world = world;
	_input = input;
}
