#include "SandboxUILayer.h"

#include "Application/Application.h"

SandboxUILayer::SandboxUILayer() : ImGuiLayer()
{
}

Shue::Application& app = Shue::Application::Get();

void SandboxUILayer::OnUpdate()
{
	ImGuiIO& io = ImGui::GetIO();
	Shue::Application& app = Shue::Application::Get();
	io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

	float time = (float)glfwGetTime();
	io.DeltaTime = Shue::DELTA_TIME;
	m_Time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Positions");
	for (auto it = app.CurrentScene.begin(); it != app.CurrentScene.end(); it++)
	{
		Shue::Entity* entity = it->second;
		ImGui::SliderFloat3(entity->GetName().c_str(), (float*)&(entity->GetTransform()->Position), -1.0f, 1.0f);
	}
	ImGui::End();

	ImGui::Begin("Debug");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
