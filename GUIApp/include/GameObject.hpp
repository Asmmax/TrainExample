#pragma once

#include <memory>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class Object;
class Model;
class SharedMesh;
class Transform;
class Material;

class GameObject
{
public:
	GameObject();
	GameObject(const std::shared_ptr<SharedMesh>& mesh);
	virtual ~GameObject() = default;

	void setMaterial(const std::shared_ptr<Material>& material);
	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& rotation);
	void setRotation(const glm::quat& rotation);
	void setScale(const glm::vec3& scale);
	void setMesh(const std::shared_ptr<SharedMesh>& mesh);

	void attachChild(const std::shared_ptr<GameObject>& child);
	const std::shared_ptr<Transform>& getTransform() { return _transform; }

	virtual void interpolate(float value) {}
	virtual void init(const std::shared_ptr<Model>& model);
	virtual void update(float delta_time);
	virtual void fixedUpdate(float fixed_time) {}

protected:
	void applyMaterial();

protected:
	std::shared_ptr<Transform> _transform;
	std::shared_ptr<SharedMesh> _mesh;
	std::shared_ptr<Material> _material;
	std::shared_ptr<Model> _model;
	Object* _object;
};
