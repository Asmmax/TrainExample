#pragma once
#include <vector>
#include <memory>

class System;
class Window;
class World;

/// @serializable @shared systemGroups
class SystemGroupAsset
{
	using SystemPtr = std::shared_ptr<System>;

private:
	std::vector<SystemPtr> _systems;

public:
	SystemGroupAsset();

	/// @inject
	void setSystems(const std::vector<SystemPtr>& systems);

	void init(Window* window);
	void attachTo(World& world);
};
