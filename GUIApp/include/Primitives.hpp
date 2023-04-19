#pragma once
#include "SharedMesh.h"

class Plane : public SharedMesh
{
public:
	Plane();
};

class Cube : public SharedMesh
{
public:
	Cube();
};

class Sphere : public SharedMesh
{
public:
	Sphere(int stacks = 8, int slices = 16);
};
