#pragma once
#include "DrawState.hpp"
#include <memory>
#include <glm/vec3.hpp>

class Batch;
class Object;
class Model;
class ShaderAsset;

/// @serializable
struct Color
{
	float r;
	float g;
	float b;
};

/// @serializable @shared materials
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

	/// @inject
	void setShader(const std::shared_ptr<ShaderAsset>& shader);
	/// @inject
	void setColor(const Color& color);
};
