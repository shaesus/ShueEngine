#include "PendulumUILayer.h"

#include <iostream>

PendulumUILayer::PendulumUILayer(Pendulum** pendulum, float& mass, float& length, float& startAngle, UIData& uiData)
	: m_Pendulum(pendulum), m_Mass(mass), m_Length(length), m_StartAngle(startAngle), m_UIData(uiData)
{
}

void PendulumUILayer::OnUpdate()
{
	ImGuiIO& io = ImGui::GetIO();
	Shue::Application& app = Shue::Application::Get();
	io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

	float time = (float)glfwGetTime();
	io.DeltaTime = Shue::DELTA_TIME;
	m_Time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Pendulum Initialization");
	ImGui::InputFloat("Mass", &m_Mass, 0.1f);
	ImGui::InputFloat("Length", &m_Length, 0.1f);
	ImGui::InputFloat("Start Angle", &m_StartAngle, 1.0f);
	m_UIData.confirmed = ImGui::Button("Confirm");
	m_UIData.getTable = ImGui::Button("Output data");
	if (ImGui::Button("Change texture"))
	{
		m_FileBrowser.SetTitle("Choose texture file");
		m_FileBrowser.SetTypeFilters({ ".jpg", ".png" });
		m_FileBrowser.Open();
	}
	if (ImGui::Button("Change model"))
	{
		m_FileBrowser.SetTitle("Choose model file");
		m_FileBrowser.SetTypeFilters({ ".obj" });
		m_FileBrowser.Open();
	}
	ImGui::End();

	m_FileBrowser.Display();

	m_UIData.fileSelected = m_FileBrowser.HasSelected();
	if (m_UIData.fileSelected)
	{
		m_UIData.filePath = m_FileBrowser.GetSelected().string();
		m_FileBrowser.ClearSelected();
	}

	ImGui::Begin("Data");
	ImGui::Text("Emax = %.2f", (*m_Pendulum)->GetEmax());
	ImGui::Text("A = %.2f\tHmax = %.2f", (*m_Pendulum)->GetAmplitude(), (*m_Pendulum)->GetHmax());
	ImGui::Text("T = %.2f\tFreq = %.2f", (*m_Pendulum)->GetPeriod(), (*m_Pendulum)->GetFrequency());
	ImGui::Text("Current Angle = %.2f", (*m_Pendulum)->GetAngleDeg());
	ImGui::Text("P = %.2f\tK = %.2f", (*m_Pendulum)->GetPotentialEnergy(), (*m_Pendulum)->GetKineticEnergy());
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}