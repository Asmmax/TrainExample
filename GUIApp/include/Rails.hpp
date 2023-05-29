#pragma once
#include "SharedMesh.hpp"
#include <memory>

class ACurve;

class Rails : public SharedMesh
{
public:
	Rails(const std::shared_ptr<ACurve>& path, float width, float gap, int seg_count = 16);
};
