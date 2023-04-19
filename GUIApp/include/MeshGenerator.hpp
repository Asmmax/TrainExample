#pragma once
#include "framework/mesh.h"
#include <memory>

class ACurve;

class MeshGenerator {
public:
	const std::vector<Vertex>& getVertices() const { return _vertices; }
	const std::vector<unsigned int>& getIndices() const { return _indices; }

	void meshPointsStrip(const std::vector<glm::vec3>& left, const std::vector<glm::vec3>& right, bool loop = true);
	void meshPoints(const std::vector<glm::vec3>& left, const std::vector<glm::vec3>& right);

private:
	std::vector<Vertex>       _vertices;
	std::vector<unsigned int> _indices;
	unsigned int _seg_count = 0;
};
