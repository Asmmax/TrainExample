#pragma once
#include "ComponentCommon.hpp"
#include <string>

class SpawnerComponent : public ComponentCommon<SpawnerComponent>
{
private:
	std::string _trainId;
	float _delay;

public:
	SpawnerComponent(const std::string& trainId, float delay);

	void init() override;

protected:
	void spawn();
};
