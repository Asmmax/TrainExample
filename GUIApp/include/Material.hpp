#pragma once
#include "DrawState.hpp"
#include <glm/vec3.hpp>
#include <string>

class Loader;
class Shader;

class Material
{
private:
	Shader* _shader;
	std::string _vertexShader;
	std::string _fragmentShader;
	glm::vec3 _color;

public:
	Material();

	void apply(DrawStateDef& state) const;
	Shader* getShader() const { return _shader; }

	void loadShader(Loader& loader);
	void setVertexShader(const std::string& shader);
	void setFragmentShader(const std::string& shader);

	void setColor(float r, float g, float b);
};
