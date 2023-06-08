#include "assets/MaterialAsset.hpp"
#include "assets/ShaderAsset.hpp"
#include "Model.hpp"
#include "objects/Batch.hpp"

MaterialAsset::MaterialAsset():
	_batch(nullptr),
	_color(1.0f, 1.0f, 1.0f)
{
}

void MaterialAsset::init(const std::shared_ptr<Model>& model)
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

Object* MaterialAsset::apply(const std::shared_ptr<Model>& model)
{
	if (!_model) {
		init(model);
	}

	if (_batch) {
		return _batch->createObject();
	}

	return nullptr;
}

void MaterialAsset::free(Object* object)
{
	if (_batch) {
		_batch->removeObject(object);
	}
}

void MaterialAsset::setShader(const std::shared_ptr<ShaderAsset>& shader)
{
	_shader = shader;
}

void MaterialAsset::setColor(const Color& color)
{
	_color.r = color.r;
	_color.g = color.g;
	_color.b = color.b;
}
