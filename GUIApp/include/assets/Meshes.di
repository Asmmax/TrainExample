bind "MeshAsset.hpp";
bind "meshes/Primitives.hpp";
bind "meshes/Rails.hpp";
bind "meshes/Sleepers.hpp";

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

shared Rails : MeshAsset
{
	Rails(ACurve path, float width, float gap, int seg_count = 16);
};

shared Sleepers : MeshAsset
{
	Sleepers(ACurve path, float thickness, float width, float step);
};
