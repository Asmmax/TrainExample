#pragma once
#include "DrawState.hpp"
#include <memory>
#include <glm/vec3.hpp>

class Batch;
class Object;
class Model;
class ShaderAsset;

class MaterialAsset
{
private:
	std::shared_ptr<Model> _model;
	std::shared_ptr<ShaderAsset> _shader;
	Batch* _batch;
	glm::vec3 _color;

public:
	MaterialAsset();

	void init(const std::shared_ptr<Model>& model);
	Object* apply(const std::shared_ptr<Model>& model);
	void free(Object* object);

	void setShader(const std::shared_ptr<ShaderAsset>& shader);
	void setColor(const glm::vec3& color);
};
