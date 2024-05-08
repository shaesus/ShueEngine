#include "UILayer.h"

namespace Shue {

	UILayer::UILayer(glm::vec3& cube, glm::vec3& light)
		: m_cube(cube), m_light(light), ImGuiLayer()
	{
	}

	UILayer::~UILayer()
	{
	}

	void UILayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Positions");
		ImGui::SliderFloat3("cube", (float*)&m_cube, -1.0f, 1.0f);
		ImGui::SliderFloat3("light", (float*)&m_light, -1.0f, 1.0f);
		ImGui::End();

		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}