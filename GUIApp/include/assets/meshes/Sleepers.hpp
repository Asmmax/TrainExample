#pragma once
#include "assets/MeshAsset.hpp"

class ACurve;

class Sleepers : public MeshAsset
{
public:
	Sleepers(ACurve* path, float thickness, float width, float step);
};

