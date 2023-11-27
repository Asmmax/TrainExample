#pragma once
#include "AComponent.hpp"
#include "GameObject.hpp"

template <typename CompType>
class ComponentCommon : public Component, public std::enable_shared_from_this<CompType>
{
public:
	using OriginType = CompType;
	using Super = ComponentCommon<CompType>;

public:
	void attachTo(GameObject& object) override;
	bool isSameType(const Component* component) const override;
};

template<typename CompType>
void ComponentCommon<CompType>::attachTo(GameObject& object)
{
	object.addComponent<CompType>(this->shared_from_this());
}

template<typename CompType>
bool ComponentCommon<CompType>::isSameType(const Component* component) const
{
	return dynamic_cast<const ComponentCommon<CompType>*>(component) != nullptr;
}
