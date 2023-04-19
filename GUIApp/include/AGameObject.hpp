#pragma once

#include <memory>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class Object;
class SharedMesh;

class GameObject
{
protected:
	using SharedMeshPtr = std::shared_ptr<SharedMesh>;

public:
	GameObject();
	GameObject(const SharedMeshPtr& mesh);
	virtual ~GameObject() = default;

	void setColor(float r, float g, float b);
	void setPosition(const glm::vec3& position) { _position = position; }
	void setRotation(const glm::vec3& rotation);
	void setRotation(const glm::quat& rotation) { _rotation = rotation; }
	void setScale(const glm::vec3& scale) { _scale = scale; }
	void setMesh(const SharedMeshPtr& mesh) { _mesh = mesh; }
	// Можно задать сдвиг для отображаемого объекта. Решение временное, замена иерархии нод.
	void setOffset(const glm::vec3& offset) { _offset = offset; }

	virtual void interpolate(float value) = 0;
	virtual void init() = 0;
	virtual void update(float delta_time) = 0;
	virtual void fixedUpdate(float fixed_time) = 0;

protected:
	glm::vec3 _position = glm::vec3(0.0f);
	glm::quat _rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 _scale = glm::vec3(1.0f);

	glm::vec3 _offset = glm::vec3(0.0f);

	SharedMeshPtr _mesh;
	Object* _object;
};
