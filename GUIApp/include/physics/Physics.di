bind "components/TrackedComponent.hpp";
bind "PhysicalSystem.hpp";

shared TrackedComponent : Component
{
	setPath(ACurve path);
	setVelocity(float velocity);
	setParameter(float param);
};

single PhysicalSystem : System
{
	PhysicalSystem(float fixedTime);
};
