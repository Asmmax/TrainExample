#pragma once
#include "assets/MeshAsset.hpp"

class Plane : public MeshAsset
{
public:
	Plane();
};

class Cube : public MeshAsset
{
public:
	Cube();
};

class Sphere : public MeshAsset
{
public:
	Sphere(int stacks = 8, int slices = 16);
};
