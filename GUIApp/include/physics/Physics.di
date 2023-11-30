bind "physics/components/TrackedComponent.hpp";
bind "physics/PhysicalSystem.hpp";

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
