bind "assets/MeshAsset.hpp";
bind "assets/meshes/Primitives.hpp";

abstract shared MeshAsset
{
} meshes;

shared Plane : MeshAsset
{
};

shared Cube : MeshAsset
{
};

shared Sphere : MeshAsset
{
	Sphere(int stacks = 8, int slices = 16);
};
