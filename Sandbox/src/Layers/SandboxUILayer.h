#pragma once

#include "Application/ImGui/ImGuiLayer.h"

#include "glm/glm.hpp"

class SandboxUILayer : public Shue::ImGuiLayer
{
public:
	SandboxUILayer(glm::vec3& cube, glm::vec3& light);
	~SandboxUILayer();

	void OnUpdate() override;

private:
	glm::vec3& m_cube;
	glm::vec3& m_light;
};
