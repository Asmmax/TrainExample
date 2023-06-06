#pragma once
#include "components/AComponent.hpp"
#include <memory>

class Model;
class RenderObject;
class Material;
class SharedMesh;
class GameObject;

class RenderComponent : public Component
{
private:
	std::shared_ptr<Model> _model;
	std::shared_ptr<RenderObject> _object;
	std::shared_ptr<Material> _material;
	std::shared_ptr<SharedMesh> _mesh;

public:
	RenderComponent();

	void init() override;

	void setMaterial(const std::shared_ptr<Material>& material);
	void setMesh(const std::shared_ptr<SharedMesh>& mesh);
};
