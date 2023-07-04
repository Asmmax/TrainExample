#pragma once
#include <vector>
#include <memory>

class InputDistributor;
class AInputAxisImpl;

/// @serializable @polymorphic
class InputAxis
{
private:
	using ImplPtr = std::shared_ptr<AInputAxisImpl>;
	std::vector<ImplPtr> _impls;

public:
	InputAxis(const std::vector<ImplPtr>& impls);

	void init(InputDistributor* distributor);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);
	float getValue() const;
};
