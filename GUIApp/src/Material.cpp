#include "Material.hpp"
#include "assets/ShaderAsset.hpp"
#include "Model.hpp"
#include "objects/Batch.hpp"

Material::Material():
	_batch(nullptr),
	_color(1.0f, 1.0f, 1.0f)
{
}

void Material::init(const std::shared_ptr<Model>& model)
{
	_model = model;
	if (_model) {
		_batch = _model->createBatch();
	}

	if (!_batch) {
		return;
	}

	auto& state = _batch->getState();
	state.addOrSet(StringId("Material.DiffuseColor"), _color);
	state.addOrSet(StringId("Material.AmbientFactor"), 0.2f);
	state.addOrSet(StringId("Material.DiffuseFactor"), 0.8f);

	if (_shader) {
		_batch->setShader(_shader->getShader());
	}
}

Object* Material::apply(const std::shared_ptr<Model>& model)
{
	if (!_model) {
		init(model);
	}

	if (_batch) {
		return _batch->createObject();
	}

	return nullptr;
}

void Material::free(Object* object)
{
	if (_batch) {
		_batch->removeObject(object);
	}
}

void Material::setShader(const std::shared_ptr<ShaderAsset>& shader)
{
	_shader = shader;
}

void Material::setColor(float r, float g, float b)
{
	_color.r = r;
	_color.g = g;
	_color.b = b;
}
