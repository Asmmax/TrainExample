bind "components/ICameraManipulator.hpp";
bind "components/RotateCameraManipulator.hpp";
bind "components/FlyCameraManipulator.hpp";
bind "components/OrbitCameraManipulator.hpp";
bind "components/ManipulatorSwitcher.hpp";
bind "components/ManipulatorSwitcherAdder.hpp";

abstract shared ICameraManipulator
{
};

shared RotateCameraManipulator : Component, ICameraManipulator
{
	RotateCameraManipulator(float rotSpeed);
};

shared FlyCameraManipulator : RotateCameraManipulator
{
	FlyCameraManipulator(float rotSpeed, float speed, float speedUpCoef);
};

shared OrbitCameraManipulator : Component, ICameraManipulator
{
	OrbitCameraManipulator(float rotSpeed, float zoomSpeed);
	setEye(TransformComponent eye);
};

shared ManipulatorSwitcher : Component
{
	ManipulatorSwitcher(vector<ICameraManipulator> manipulators);
};

shared ManipulatorSwitcherAdder : Component
{
	ManipulatorSwitcherAdder(ICameraManipulator manipulator);
};
