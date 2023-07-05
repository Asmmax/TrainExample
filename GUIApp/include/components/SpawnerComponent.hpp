#pragma once
#include "AComponent.hpp"

/// @serializable
class SpawnerComponent : public ComponentCommon<SpawnerComponent>
{
private:
	std::string _trainId;

public:
	SpawnerComponent(const std::string& trainId);

	void init() override;

protected:
	void spawn();
};
