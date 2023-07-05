#pragma once
#include <functional>
#include <vector>
#include <unordered_map>

class InputDistributor;

/// @serializable @polymorphic @abstract
class AInputAxisImpl
{
private:
	using ActionEvent = std::unordered_map<void*, std::vector<std::function<void(float)>>>;
	ActionEvent _actionChanged;
	float _value;
	float _smooth;
	float _minSpeed;

public:
	AInputAxisImpl(float smooth, float minSpeed);

	virtual void init(InputDistributor* distributor) = 0;
	virtual void update(float deltaTime) = 0;

	virtual void fixedUpdate(float deltaTime);

	void bindToChanged(void* owner, const std::function<void(float)>& callback);
	void unbindAllChanged(void* owner);
	float getValue() const;

protected:
	virtual float getRawValue() const = 0;

	void broadcastChanged();
	void setValue(float value);
};
