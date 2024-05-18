#include "SandboxUILayer.h"

#include "Application/Application.h"

#include "ECS/Transform.h"
#include "ECS/ModelRenderer.h"

#include <vector>

static Shue::Application& app = Shue::Application::Get();
static int selectedIndex;
static Shue::Entity* selectedObject;

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

	ImGui::Begin("Scene Manager");
	std::vector<const char*> sceneObjects = app.CurrentScene.GetObjectsList();
	ImGui::ListBox("Scene Objects", &selectedIndex, sceneObjects.data(), sceneObjects.size());
	ImGui::End();

	ImGui::Begin("Component Manager");
	selectedObject = app.CurrentScene[sceneObjects[selectedIndex]];
	for (auto it = selectedObject->begin(); it != selectedObject->end(); it++)
	{
		Shue::Component* comp = it->second;
		switch (comp->GetType())
		{
		case Shue::ComponentType::TransformComp:
		{
			ImGui::Text("Transform");
			Shue::Transform* transform = (Shue::Transform*)comp;
			ImGui::SliderFloat3("Position", (float*)&(transform->Position), -1.0f, 1.0f);
			ImGui::InputFloat3("Scale", (float*)&(transform->Scale));
			break;
		}
		case Shue::ComponentType::ModelRendererComp:
		{
			ImGui::Text("Model Renderer");
			Shue::ModelRenderer* modelRenderer = (Shue::ModelRenderer*)comp;
			break;
		}
		default:
			break;
		}
	}
	ImGui::End();

	ImGui::Begin("Debug");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
