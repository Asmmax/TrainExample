bind "SceneAsset.hpp";
bind "units/OverriddenSceneUnit.hpp";
bind "units/SceneUnit.hpp";

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
