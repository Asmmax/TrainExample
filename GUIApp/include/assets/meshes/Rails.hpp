#pragma once
#include "assets/MeshAsset.hpp"
#include <memory>

class ACurve;

class Rails : public MeshAsset
{
public:
	Rails(const std::shared_ptr<ACurve>& path, float width, float gap, int seg_count = 16);
};
