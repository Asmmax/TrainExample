#include "MeshGenerator.hpp"
#include "ACurve.hpp"
#include <glm/gtx/normal.hpp>

MeshGenerator::MeshGenerator()
{
	_data.primitiveSize = 3;
}

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

		_data.textureCoords.push_back(glm::vec2(0.f, 0.f));
		_data.textureCoords.push_back(glm::vec2(1.f, 0.f));
		_data.textureCoords.push_back(glm::vec2(1.f, 1.f));
		_data.textureCoords.push_back(glm::vec2(0.f, 1.f));

		auto normal = glm::triangleNormal(left[i % points_count], right[i % points_count], right[(i + 1) % points_count]);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);

		auto tangent = glm::normalize(right[(i + 1) % points_count] - right[i % points_count] + left[(i + 1) % points_count] - left[i % points_count]);
		_data.tangents.push_back(tangent);
		_data.tangents.push_back(tangent);
		_data.tangents.push_back(tangent);
		_data.tangents.push_back(tangent);

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

		_data.textureCoords.push_back(glm::vec2(0.f, 0.f));
		_data.textureCoords.push_back(glm::vec2(1.f, 0.f));
		_data.textureCoords.push_back(glm::vec2(1.f, 1.f));
		_data.textureCoords.push_back(glm::vec2(0.f, 1.f));

		auto normal = glm::triangleNormal(left[(i << 1) + 0], right[(i << 1) + 0], right[(i << 1) + 1]);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);
		_data.normals.push_back(normal);

		auto tangent = glm::normalize(right[(i << 1) + 1] - right[(i << 1) + 0] + left[(i << 1) + 1] - left[(i << 1) + 0]);
		_data.tangents.push_back(tangent);
		_data.tangents.push_back(tangent);
		_data.tangents.push_back(tangent);
		_data.tangents.push_back(tangent);

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
