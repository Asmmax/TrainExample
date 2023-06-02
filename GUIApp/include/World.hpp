#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

class GameObject;
class System;
class Window;
class ICameraView;
class Transform;
class Model;

class World
{
	using GameObjectPtr = std::shared_ptr<GameObject>;
	using SystemPtr = std::shared_ptr<System>;
	using CameraViewPtr = std::shared_ptr<ICameraView>;

public:
	World();
	~World();

	void AddGameObject(const GameObjectPtr& game_object);

	CameraViewPtr getMainCameraView() const;
	CameraViewPtr CreateCameraView(int width, int height);

	template<typename SysType, typename... Args>
	std::shared_ptr<SysType> addSystem(Args&&... args);

	template<typename SysType>
	std::shared_ptr<SysType> getSystem() const;

	const std::shared_ptr<Model>& getModel() const { return _model; }

	void init(Window* window);
	void update(float delta_time);
	void draw();

private:
	bool _isInited;

	Window* _window;
	std::shared_ptr<Model> _model;

	CameraViewPtr _mainCamera;
	std::vector<CameraViewPtr> _cameras;

	std::vector<GameObjectPtr> _game_objects;

	std::vector<SystemPtr> _systems;
	std::unordered_map<std::type_index, SystemPtr> _systemsMap;
};

template<typename SysType, typename... Args>
std::shared_ptr<SysType> World::addSystem(Args&&... args)
{
	std::type_index index = std::type_index(typeid(SysType));
	assert(_systemsMap.count(index) == 0);

	auto sysTypePtr = std::shared_ptr<SysType>(new SysType(std::forward<Args>(args)...));
	_systems.emplace_back(sysTypePtr);
	_systemsMap.emplace(index, sysTypePtr);
	return sysTypePtr;
}

template<typename SysType>
std::shared_ptr<SysType> World::getSystem() const
{
	std::type_index index = std::type_index(typeid(SysType));

	auto foundIt = _systemsMap.find(index);
	if (foundIt != _systemsMap.end()) {
		return std::static_pointer_cast<SysType>(foundIt->second);
	}
	return nullptr;
}
