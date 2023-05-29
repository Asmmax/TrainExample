#pragma once
#include "SharedMesh.hpp"
#include <memory>

class ACurve;

class Sleepers : public SharedMesh
{
public:
	Sleepers(const std::shared_ptr<ACurve>& path, float thickness, float width, float step);
};

