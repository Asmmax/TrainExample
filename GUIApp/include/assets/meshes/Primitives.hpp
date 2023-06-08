#pragma once
#include "assets/MeshAsset.hpp"

/// @serializable
class Plane : public MeshAsset
{
public:
	Plane();
};

/// @serializable
class Cube : public MeshAsset
{
public:
	Cube();
};

/// @serializable
class Sphere : public MeshAsset
{
public:
	Sphere(int stacks = 8, int slices = 16);
};
