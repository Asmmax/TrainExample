#pragma once

#include <memory>
#include <vector>

class GameObject;
class Window;
class ICameraView;
class Transform;
class Model;
class Light;

class World
{
	using GameObjectPtr = std::shared_ptr<GameObject>;
	using CameraViewPtr = std::shared_ptr<ICameraView>;

public:
	World(float fixed_time);
	~World();

	void AddGameObject(const GameObjectPtr& game_object);

	CameraViewPtr getMainCameraView() const;
	CameraViewPtr CreateCameraView(int width, int height);

	const std::shared_ptr<Model>& getModel() const { return _model; }

	void init(Window* window);
	void update(float delta_time);
	void draw();

private:
	void fixedUpdate();

private:
	float _fixed_time;
	float _time_redundant;
	bool _isInited;
	Window* _window;
	Light* _mainLight;
	CameraViewPtr _mainCamera;
	std::shared_ptr<Model> _model;
	std::vector<GameObjectPtr> _game_objects;
	std::vector<CameraViewPtr> _cameras;
};
