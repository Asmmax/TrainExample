bind "assets/meshes/Rails.hpp";
bind "assets/meshes/Sleepers.hpp";

shared Rails : MeshAsset
{
	Rails(ACurve path, float width, float gap, int seg_count = 16);
};

shared Sleepers : MeshAsset
{
	Sleepers(ACurve path, float thickness, float width, float step);
};
