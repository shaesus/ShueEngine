#include "PendulumUILayer.h"

#include <iostream>

PendulumUILayer::PendulumUILayer(float& mass, float& length, float& startAngle, bool& confirmed)
	: m_Mass(mass), m_Length(length), m_StartAngle(startAngle), m_Confirmed(confirmed)
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
	m_Confirmed = ImGui::Button("Confirm");
	ImGui::End();

	ImGui::Begin("Data");
	ImGui::End();

	ImGui::Begin("Debug");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
