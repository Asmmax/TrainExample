#pragma once
#include "ASystem.hpp"
#include "World.hpp"
#include <memory>

template<typename SystemType>
class SystemCommon : public System, public std::enable_shared_from_this<SystemType>
{
public:
	using OriginType = SystemType;

public:
	void attachTo(World& world) override;
};

template<typename SystemType>
void SystemCommon<SystemType>::attachTo(World& world)
{
	world.addSystem<SystemType>(this->shared_from_this());
}
