bind "assets/units/SceneObjectReader.hpp";
bind "assets/units/SceneUnit.hpp";
bind "assets/units/OverriddenSceneUnit.hpp";
bind "assets/SceneAsset.hpp";

shared SceneAsset
{
	SceneAsset(vector<SceneUnit> units);
} scenes;

shared SceneUnit
{
	SceneUnit(vector<vector<Component>> objects);
} units;

value SceneObjectChange 
{
	unsigned int objectId;
	vector<Component> overrides;
};

value SceneUnitChange
{
	SceneUnit original;
	vector<SceneObjectChange> changes;
};

shared OverriddenSceneUnit : SceneUnit
{
	OverriddenSceneUnit(vector<vector<Component>> objects, vector<SceneUnitChange> units);
};
