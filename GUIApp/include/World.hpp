#pragma once

#include <memory>
#include <vector>

class ACurve;
class GameObject;

class World
{
	using GameObjectPtr = std::shared_ptr<GameObject>;

public:
	World(float fixed_time);
	~World();

	void AddGameObject(const GameObjectPtr& game_object);

	void init();
	void draw();
	void update(float delta_time);

private:
	void fixedUpdate();

private:
	float _fixed_time;
	float _time_redundant;
	std::shared_ptr<ACurve> _path;
	std::vector<GameObjectPtr> _game_objects;
};
