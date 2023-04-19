#include "StaticObject.hpp"
#include "SharedMesh.hpp"
#include "framework/engine.h"

StaticObject::StaticObject() : GameObject::GameObject()
{
}

StaticObject::StaticObject(const SharedMeshPtr& mesh) : GameObject::GameObject(mesh)
{
}

void StaticObject::init()
{
	_object->setPosition(_position + _offset);
	_object->setRotation(_rotation);
	_object->setScale(_scale);
}
