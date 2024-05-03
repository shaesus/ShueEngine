#pragma once

#include "Application/Layer.h"

#include "Application/Events/KeyEvent.h"
#include "Application/Events/MouseEvent.h"
#include "Application/Events/ApplicationEvent.h"

#include "Application/Application.h"

#include "Core.h"

#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_opengl3.h"

//TEMPORARY
#include "GLFW/glfw3.h"

namespace Shue {

	class SHUE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const std::string& name = "ImGuiLayer");
		virtual ~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		virtual void OnUpdate();
		void OnEvent(Event& e);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	protected:
		float m_Time = 0.0f;
	};

}