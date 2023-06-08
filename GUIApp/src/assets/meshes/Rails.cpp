#include "assets/meshes/Rails.hpp"
#include "ACurve.hpp"
#include "MeshGenerator.hpp"
#include "ParallelCurve.hpp"

Rails::Rails(const std::shared_ptr<ACurve>& path, float width, float gap, int seg_count)
{
	auto parameters = path->getUniformDistribution(seg_count + 1);

	MeshGenerator generator;

	//left rail
	ParallelCurve left_rail_beg(path, glm::vec3(-gap / 2 - width, 0, 0));
	ParallelCurve left_rail_end(path, glm::vec3(-gap / 2, 0, 0));
	generator.meshPointsStrip(left_rail_beg.getValues(parameters), left_rail_end.getValues(parameters));

	//right rail
	ParallelCurve right_rail_beg(path, glm::vec3(gap / 2, 0, 0));
	ParallelCurve right_rail_end(path, glm::vec3(gap / 2 + width, 0, 0));
	generator.meshPointsStrip(right_rail_beg.getValues(parameters), right_rail_end.getValues(parameters));

	_data = generator.getMeshData();
}
