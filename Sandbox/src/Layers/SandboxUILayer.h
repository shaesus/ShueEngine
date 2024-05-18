#pragma once

#include "Application/ImGui/ImGuiLayer.h"

#include "ECS/Transform.h"

#include "glm/glm.hpp"

class SandboxUILayer : public Shue::ImGuiLayer
{
public:
	SandboxUILayer();

	void OnUpdate() override;
};
