#pragma once
#include "resources/MeshData.hpp"
#include <memory>

class ACurve;

class MeshGenerator {
public:
	const MeshData& getMeshData() const { return _data; }

	void meshPointsStrip(const std::vector<glm::vec3>& left, const std::vector<glm::vec3>& right, bool loop = true);
	void meshPoints(const std::vector<glm::vec3>& left, const std::vector<glm::vec3>& right);

private:
	MeshData _data;
	unsigned int _seg_count = 0;
};
