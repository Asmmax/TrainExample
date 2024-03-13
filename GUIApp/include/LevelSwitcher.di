bind "components/LevelSwitcherComponent.hpp";
bind "systems/LevelManager.hpp";

shared LevelSwitcherComponent : Component
{
};

single LevelManager : System
{
	LevelManager(vector<std::string> levels, std::string currentLevel);
};
