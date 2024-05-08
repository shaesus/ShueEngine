#pragma once

#include "Application/ImGui/ImGuiLayer.h"

class PendulumUILayer : public Shue::ImGuiLayer
{
public:
	PendulumUILayer(float& mass, float& length, float& startAngle, bool& confirmed);

	void OnUpdate() override;

private:
	float& m_Mass;
	float& m_Length;
	float& m_StartAngle;
	bool& m_Confirmed;
};
