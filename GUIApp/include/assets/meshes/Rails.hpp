#pragma once
#include "assets/MeshAsset.hpp"

class ACurve;

class Rails : public MeshAsset
{
public:
	Rails(ACurve* path, float width, float gap, int seg_count = 16);
};
