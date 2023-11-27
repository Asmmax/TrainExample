bind "components/CameraComponent.hpp";
bind "../Vec3Reader.hpp";
bind "components/LightComponent.hpp";
bind "components/RenderComponent.hpp";
bind "RenderSystem.hpp";

shared CameraComponent : Component
{
	CameraComponent(bool isMain = false);
};

shared LightComponent : Component
{
	setRadius(float radius);
	setFadingArea(float fadingArea);
	setIntensity(float intensity);
	setColor(glm::vec3 color);
};

shared RenderComponent : Component
{
	setMaterial(MaterialAsset material);
	setMesh(MeshAsset mesh);
};

single RenderSystem : System
{
};
