bind "units/SceneObjectReader.hpp";
bind "units/SceneUnit.hpp";
bind "units/OverriddenSceneUnit.hpp";
bind "SceneAsset.hpp";

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
