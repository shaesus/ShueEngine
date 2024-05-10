#pragma once

#include "Application/ImGui/ImGuiLayer.h"

#include "../Entities/Pendulum.h"

struct UIData
{
	bool confirmed;
	bool getTable;
	bool fileSelected;
	std::string filePath;
};

class PendulumUILayer : public Shue::ImGuiLayer
{
public:
	PendulumUILayer(Pendulum** pendulum, float& mass, float& length, float& startAngle, UIData& uiData);

	void OnUpdate() override;

private:
	ImGui::FileBrowser m_FileBrowser;

	float& m_Mass;
	float& m_Length;
	float& m_StartAngle;

	UIData& m_UIData;

	Pendulum** m_Pendulum;
};
