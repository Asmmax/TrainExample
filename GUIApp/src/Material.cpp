#include "Material.hpp"
#include "Loader.hpp"

Material::Material():
	_shader(nullptr),
	_vertexShader(""),
	_fragmentShader(""),
	_color(1.0f, 1.0f, 1.0f)
{
}

void Material::apply(DrawStateDef& state) const
{
	state.addOrSet(StringId("Material.DiffuseColor"), _color);
	state.addOrSet(StringId("Material.AmbientFactor"), 0.2f);
	state.addOrSet(StringId("Material.DiffuseFactor"), 0.8f);
}

void Material::loadShader(Loader& loader)
{
	_shader = loader.loadShader(_vertexShader, _fragmentShader);
}

void Material::setVertexShader(const std::string& shader)
{
	_vertexShader = shader;
}

void Material::setFragmentShader(const std::string& shader)
{
	_fragmentShader = shader;
}

void Material::setColor(float r, float g, float b)
{
	_color.r = r;
	_color.g = g;
	_color.b = b;
}
