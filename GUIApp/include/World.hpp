#pragma once

#include <memory>
#include <vector>

class GameObject;
class APlayerController;
class InputController;
class Window;
class ICameraView;
class Transform;
class Model;
class Light;

class World
{
	using GameObjectPtr = std::shared_ptr<GameObject>;
	using PlayerControllerPtr = std::shared_ptr<APlayerController>;
	using CameraViewPtr = std::shared_ptr<ICameraView>;

public:
	World(float fixed_time);
	~World();

	void AddGameObject(const GameObjectPtr& game_object);
	void AddPlayerController(const PlayerControllerPtr& playerController);

	void setInput(const std::shared_ptr<InputController>& input);

	CameraViewPtr getMainCameraView() const;
	CameraViewPtr CreateCameraView(int width, int height);

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
	std::shared_ptr<Transform> _root;
	std::vector<GameObjectPtr> _game_objects;
	std::vector<PlayerControllerPtr> _playerControllers;
	std::vector<CameraViewPtr> _cameras;
	std::shared_ptr<InputController> _input;
};
