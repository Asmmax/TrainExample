#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>
#include <vector>

class Transform
{
private:
	glm::vec3 _localPosition;
	glm::quat _localRotation;
	glm::vec3 _localScale;
	std::vector<std::shared_ptr<Transform>> _children;
	Transform* _parent;
	glm::mat4 _parentMatrix;
	mutable glm::mat4 _localMatrix;
	mutable glm::mat4 _globalMatrix;
	mutable bool _dirtyLocalMatrix;
	mutable bool _dirtyGlobalMatrix;
#ifdef _DEBUG
	bool _invalidMatrices = false;
#endif // _DEBUG


public:
	Transform(const glm::vec3& localPosition = glm::vec3(0.0f),
		const glm::quat& localRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		const glm::vec3& localScale = glm::vec3(1.0f));

	void setParentMatrix(const glm::mat4& matrix = glm::mat4(1.0f));

	const Transform* getParent() const { return _parent; }

#ifdef _DEBUG
	void invalidate();
#endif // _DEBUG

	void setPosition(const glm::vec3& localPosition);
	void setRotation(const glm::quat& localRotation);
	void setScale(const glm::vec3& localScale);

	const glm::vec3& getLocalPosition() const { return _localPosition; }
	const glm::quat& getLocalRotation() const { return _localRotation; }
	const glm::vec3& getLocalScale() const { return _localScale; }
	glm::vec3 getLocalEulerAngles() const;
	glm::vec3 getLocalRight() const;
	glm::vec3 getLocalUp() const;
	glm::vec3 getLocalForward() const;

	glm::vec3 getGlobalPosition() const;

	void addChild(const std::shared_ptr<Transform>& child);
	void removeChild(const std::shared_ptr<Transform>& child);

	const glm::mat4& getLocalMatrix() const;
	const glm::mat4& getGlobalMatrix() const;
	void compute();
protected:
	void computeGlobalMatrix() const;
	void computeLocalMatrix() const;

	void setParent(Transform* parent);

#ifdef _DEBUG
	void invalidateChildren();
#endif // _DEBUG
};
