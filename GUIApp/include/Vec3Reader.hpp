#pragma once
#include "Containers/Context.hpp"
#include "Containers/IReaderStrategy.hpp"
#include <glm/vec3.hpp>

DECLARE_READER(glm::vec3)

class Vec3Reader : public IReaderStrategy<glm::vec3>
{
public:
	glm::vec3 Create(const nlohmann::json& node) override
	{
		return glm::vec3{ node[0].get<float>(), node[1].get<float>(), node[2].get<float>() };
	}

	void Init(const nlohmann::json& /*node*/) override
	{
	}
};


template<>
inline std::shared_ptr<IReaderStrategy<glm::vec3>> Context::GetReader()
{
	return std::make_shared<Vec3Reader>();
}