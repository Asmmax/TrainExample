#include "common/Transform.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

const float pi = 3.1415926536f;

Transform::Transform(const glm::vec3& localPosition,
	const glm::quat& localRotation,
	const glm::vec3& localScale) :
	_localPosition(localPosition),
	_localRotation(localRotation),
	_localScale(localScale),
	_parent(nullptr),
	_parentMatrix(1.0f),
	_localMatrix(1.0f),
	_globalMatrix(1.0f),
	_dirtyLocalMatrix(true),
	_dirtyGlobalMatrix(true)
{
}

void Transform::setParentMatrix(const glm::mat4& matrix)
{
	_parentMatrix = matrix;
	_dirtyGlobalMatrix = true;

#ifdef _DEBUG
	_invalidMatrices = false;
#endif // _DEBUG

}

#ifdef _DEBUG
void Transform::invalidate()
{
	_invalidMatrices = true;
	invalidateChildren();
}
#endif // _DEBUG

void Transform::setPosition(const glm::vec3& localPosition)
{
	_localPosition = localPosition;
	_dirtyLocalMatrix = true;

#ifdef _DEBUG
	invalidateChildren();
#endif // _DEBUG
}

void Transform::setRotation(const glm::quat& localRotation)
{
	_localRotation = glm::normalize(localRotation);
	_dirtyLocalMatrix = true;

#ifdef _DEBUG
	invalidateChildren();
#endif // _DEBUG
}

void Transform::setScale(const glm::vec3& localScale)
{
	_localScale = localScale;
	_dirtyLocalMatrix = true;

#ifdef _DEBUG
	invalidateChildren();
#endif // _DEBUG
}

glm::vec3 Transform::getGlobalPosition() const
{
	return getGlobalMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Transform::addChild(const std::shared_ptr<Transform>& child)
{
	_children.emplace_back(child);
	child->setParent(this);
}

void Transform::removeChild(const std::shared_ptr<Transform>& child)
{
	auto lastIt = std::remove(_children.begin(), _children.end(), child);
	_children.erase(lastIt, _children.end());
	child->setParent(nullptr);
}

const glm::mat4& Transform::getLocalMatrix() const
{
	if (_dirtyLocalMatrix) {
		computeLocalMatrix();
	}
	return _localMatrix;
}

const glm::mat4& Transform::getGlobalMatrix() const
{
#ifdef _DEBUG
	assert(!_invalidMatrices);
#endif // _DEBUG

	if (_dirtyGlobalMatrix || _dirtyLocalMatrix) {
		computeGlobalMatrix();
	}
	return _globalMatrix;
}

void Transform::compute()
{
#ifdef _DEBUG
	if (!_parent) {
		_invalidMatrices = false;
	}
#endif // _DEBUG

	auto& globalMatrix = getGlobalMatrix();
	for (auto child : _children)
	{
		child->setParentMatrix(globalMatrix);
		child->compute();
	}
}

void Transform::computeGlobalMatrix() const
{
	auto& localMatrix = getLocalMatrix();
	_globalMatrix = _parentMatrix * localMatrix;
	_dirtyGlobalMatrix = false;
}

void Transform::computeLocalMatrix() const
{
	glm::mat4 rotationMatrix = glm::toMat4(_localRotation);
	_localMatrix = glm::translate(_localPosition) * rotationMatrix * glm::scale(_localScale);
	_dirtyLocalMatrix = false;
}

void Transform::setParent(Transform* parent)
{
	_parent = parent;
}

#ifdef _DEBUG
void Transform::invalidateChildren()
{
	for (auto child : _children)
	{
		child->invalidate();
	}
}
#endif // _DEBUG
