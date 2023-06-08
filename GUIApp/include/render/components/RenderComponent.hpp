#pragma once
#include "AComponent.hpp"
#include <memory>

class Model;
class RenderObject;
class MaterialAsset;
class SharedMesh;
class GameObject;

class RenderComponent : public Component
{
private:
	std::shared_ptr<Model> _model;
	std::shared_ptr<RenderObject> _object;
	std::shared_ptr<MaterialAsset> _material;
	std::shared_ptr<SharedMesh> _mesh;

public:
	RenderComponent();

	void init() override;

	void setMaterial(const std::shared_ptr<MaterialAsset>& material);
	void setMesh(const std::shared_ptr<SharedMesh>& mesh);
};
