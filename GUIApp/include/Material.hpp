#pragma once
#include "DrawState.hpp"
#include <memory>
#include <glm/vec3.hpp>
#include <string>

class Loader;
class Shader;
class Batch;
class Object;
class Model;

class Material
{
private:
	std::shared_ptr<Model> _model;
	Shader* _shader;
	Batch* _batch;
	std::string _vertexShader;
	std::string _fragmentShader;
	glm::vec3 _color;

public:
	Material();

	void init(const std::shared_ptr<Model>& model);
	Object* apply(const std::shared_ptr<Model>& model);
	void free(Object* object);

	Shader* getShader() const { return _shader; }

	void loadShader(Loader& loader);
	void setVertexShader(const std::string& shader);
	void setFragmentShader(const std::string& shader);

	void setColor(float r, float g, float b);
};
