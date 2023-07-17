#pragma once
#include <memory>

class Model;
class Object;
class MaterialAsset;
class MeshAsset;
class Transform;

class RenderObject
{
private:
	std::shared_ptr<Model> _model;
	std::shared_ptr<MaterialAsset> _material;
	std::shared_ptr<MeshAsset> _mesh;
	std::shared_ptr<Transform> _transform;
	Object* _object;

public:
	RenderObject(const std::shared_ptr<Model>& model, const std::shared_ptr<MeshAsset>& mesh, const std::shared_ptr<MaterialAsset>& material, const std::shared_ptr<Transform>& transform);

	void init();
	void deinit();
	void update();

	void setMaterial(const std::shared_ptr<MaterialAsset>& material);
	void setMesh(const std::shared_ptr<MeshAsset>& mesh);

private:
	void applyMaterial();
};
