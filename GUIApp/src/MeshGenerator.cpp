#include "MeshGenerator.hpp"
#include "ACurve.hpp"

void MeshGenerator::meshPointsStrip(const std::vector<glm::vec3>& left, const std::vector<glm::vec3>& right, bool loop)
{
	assert(left.size() == right.size());
	unsigned int points_count = static_cast<unsigned int>(left.size());
	unsigned int seg_count = loop ? points_count : points_count - 1;

	for (unsigned int i = 0; i < seg_count; i++) {
		_vertices.push_back({ left[i % points_count], glm::vec3(0,1,0), glm::vec2(0,0) });
		_vertices.push_back({ right[i % points_count], glm::vec3(0,1,0), glm::vec2(1,0) });
		_vertices.push_back({ right[(i + 1) % points_count], glm::vec3(0,1,0), glm::vec2(1,1) });
		_vertices.push_back({ left[(i + 1) % points_count], glm::vec3(0,1,0), glm::vec2(0,1) });

		unsigned int startId = 4 * (i + _seg_count);
		_indices.push_back(startId + 0);
		_indices.push_back(startId + 1);
		_indices.push_back(startId + 2);
		_indices.push_back(startId + 2);
		_indices.push_back(startId + 3);
		_indices.push_back(startId + 0);
	}

	_seg_count += seg_count;
}

void MeshGenerator::meshPoints(const std::vector<glm::vec3>& left, const std::vector<glm::vec3>& right)
{
	assert(left.size() == right.size());
	assert(left.size() % 2 == 0);

	unsigned int seg_count = static_cast<unsigned int>(left.size() / 2);

	for (unsigned int i = 0; i < seg_count; i++) {
		_vertices.push_back({ left[2 * i + 0], glm::vec3(0,1,0), glm::vec2(0,0) });
		_vertices.push_back({ right[2 * i + 0], glm::vec3(0,1,0), glm::vec2(1,0) });
		_vertices.push_back({ right[2 * i + 1], glm::vec3(0,1,0), glm::vec2(1,1) });
		_vertices.push_back({ left[2 * i + 1], glm::vec3(0,1,0), glm::vec2(0,1) });

		unsigned int startId = 4 * (i + _seg_count);
		_indices.push_back(startId + 0);
		_indices.push_back(startId + 1);
		_indices.push_back(startId + 2);
		_indices.push_back(startId + 2);
		_indices.push_back(startId + 3);
		_indices.push_back(startId + 0);
	}

	_seg_count += seg_count;
}
