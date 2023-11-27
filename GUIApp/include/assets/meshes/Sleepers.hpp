#pragma once
#include "assets/MeshAsset.hpp"
#include <memory>

class ACurve;

class Sleepers : public MeshAsset
{
public:
	Sleepers(const std::shared_ptr<ACurve>& path, float thickness, float width, float step);
};

