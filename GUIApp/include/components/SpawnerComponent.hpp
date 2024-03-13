#pragma once
#include "ComponentCommon.hpp"
#include <string>
#include <list>

class GameObject;

class SpawnerComponent : public ComponentCommon<SpawnerComponent>
{
private:
	struct SpawnTask
	{
		size_t taskId;
		std::vector<std::weak_ptr<GameObject>> spawnedObjects;
	};

private:
	std::list<SpawnTask> _delayTasks;
	std::string _trainId;
	float _delay;

public:
	SpawnerComponent(const std::string& trainId, float delay);

	void init() override;
	void deinit() override;

protected:
	void spawn();
};
