#include "AGameObject.hpp"
#include "SharedMesh.hpp"
#include "framework/engine.h"

GameObject::GameObject()
{
	_object = Engine::get()->createObject();
}

GameObject::GameObject(const SharedMeshPtr& mesh):
	_mesh(mesh)
{
	assert(_mesh);
	_object = Engine::get()->createObject(_mesh->getMesh());
}

void GameObject::setColor(float r, float g, float b)
{
	_object->setColor(r, g, b);
}

void GameObject::setRotation(const glm::vec3& rotation)
{
	glm::vec3 euler = glm::radians(rotation);
	_rotation = glm::quat(euler);
}
