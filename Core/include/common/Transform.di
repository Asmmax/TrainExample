bind "Vec3Reader.hpp";
bind "common/components/TransformComponent.hpp";
bind "common/TransformSystem.hpp";

shared TransformComponent : Component
{
	TransformComponent(vector<TransformComponent> children);
	setPosition(glm::vec3 position);
	setRotation(glm::vec3 rotation);
	setScale(glm::vec3 scale);
};

single TransformSystem : System
{
};
