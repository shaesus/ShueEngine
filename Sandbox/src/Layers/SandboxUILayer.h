#pragma once

#include "Application/ImGui/ImGuiLayer.h"

class SandboxUILayer : public Shue::ImGuiLayer
{
public:
	void OnUpdate() override;
};
