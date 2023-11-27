bind "components/PlayerController.hpp";
bind "systems/PlayerManager.hpp";

shared PlayerController : Component
{
	setManipulator(ICameraManipulator target);
};

single PlayerManager : System
{
};
