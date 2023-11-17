#pragma once
#include <vector>
#include <memory>
#include <functional>

class InputDistributor;
class AInputAxisImpl;
class EventListener;

/// @serializable @polymorphic
class InputAxis
{
private:
	using ImplPtr = std::shared_ptr<AInputAxisImpl>;
	std::vector<ImplPtr> _impls;

public:
	InputAxis(const std::vector<ImplPtr>& impls);

	void init(InputDistributor* distributor);
	void startFrame(float frameTime);
	void update(float deltaTime);
	void endFrame(float frameRedutant);
	float getValue() const;

	void bindToChanged(EventListener* owner, const std::function<void(float)>& callback);
	void unbindAllChanged(EventListener* owner);
};
