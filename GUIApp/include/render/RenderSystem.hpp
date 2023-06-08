#pragma once
#include "ASystem.hpp"
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

class Window;
class CameraView;
class RenderObject;
class RenderPointLight;
class Model;
class MeshAsset;
class MaterialAsset;
class Transform;

class RenderSystem : public System
{
	using CameraViewPtr = std::shared_ptr<CameraView>;
	using RenderObjectPtr = std::shared_ptr<RenderObject>;
	using RenderPointLightPtr = std::shared_ptr<RenderPointLight>;

private:
	Window* _window;
	std::shared_ptr<Model> _model;

	CameraViewPtr _mainCamera;
	std::vector<CameraViewPtr> _cameras;
	std::vector<RenderObjectPtr> _objects;
	std::vector<RenderPointLightPtr> _pointLights;

public:
	RenderSystem(Window* window);

	void init() override;
	void update(float delta_time) override;
	void draw() override;

	CameraViewPtr createCameraView(const std::shared_ptr<Transform>& transform);
	void setMainView(const CameraViewPtr& view);

	RenderObjectPtr createObject(const std::shared_ptr<MeshAsset>& mesh, const std::shared_ptr<MaterialAsset>& material, const std::shared_ptr<Transform>& transform);
	RenderPointLightPtr createPointLight(float radius, float fadingArea, float intensity, const glm::vec3& color, const std::shared_ptr<Transform>& transform);
};
