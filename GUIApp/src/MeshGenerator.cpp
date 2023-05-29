#include "MeshGenerator.hpp"
#include "ACurve.hpp"
#include <glm/gtx/normal.hpp>

void MeshGenerator::meshPointsStrip(const std::vector<glm::vec3>& left, const std::vector<glm::vec3>& right, bool loop)
{
	assert(left.size() == right.size());
	unsigned int points_count = static_cast<unsigned int>(left.size());
	unsigned int seg_count = loop ? points_count : points_count - 1;

	for (unsigned int i = 0; i < seg_count; i++) {
		_data.positions.push_back(left[i % points_count]);
		_data.positions.push_back(right[i % points_count]);
		_data.positions.push_back(right[(i + 1) % points_count]);
		_data.positions.push_back(left[(i + 1) % points_count]);

		auto normal = glm::triangleNormal(left[i % points_count], right[i % points_count], right[(i + 1) % points_count]);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);

		unsigned int startId = 4 * (i + _seg_count);
		_data.indices.push_back(startId + 0);
		_data.indices.push_back(startId + 1);
		_data.indices.push_back(startId + 2);
		_data.indices.push_back(startId + 2);
		_data.indices.push_back(startId + 3);
		_data.indices.push_back(startId + 0);
	}

	_seg_count += seg_count;
}

void MeshGenerator::meshPoints(const std::vector<glm::vec3>& left, const std::vector<glm::vec3>& right)
{
	assert(left.size() == right.size());
	assert(left.size() % 2 == 0);

	unsigned int seg_count = static_cast<unsigned int>(left.size() / 2);

	for (unsigned int i = 0; i < seg_count; i++) {
		_data.positions.push_back(left[(i << 1) + 0]);
		_data.positions.push_back(right[(i << 1) + 0]);
		_data.positions.push_back(right[(i << 1) + 1]);
		_data.positions.push_back(left[(i << 1) + 1]);

		auto normal = glm::triangleNormal(left[(i << 1) + 0], right[(i << 1) + 0], right[(i << 1) + 1]);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);

		unsigned int startId = 4 * (i + _seg_count);
		_data.indices.push_back(startId + 0);
		_data.indices.push_back(startId + 1);
		_data.indices.push_back(startId + 2);
		_data.indices.push_back(startId + 2);
		_data.indices.push_back(startId + 3);
		_data.indices.push_back(startId + 0);
	}

	_seg_count += seg_count;
}
