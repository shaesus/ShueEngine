#pragma once
#include "Core.h"

#include <memory>

#include "Window.h"
#include "Renderer.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Shue {

	class SHUE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

		void OnEvent(Event& e);

		inline float DeltaTime() { return m_CurrentFrame - m_LastFrame; }

	protected:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnAppUpdate(AppUpdateEvent& e);
		bool OnMouseMove(MouseMovedEvent& e);
		bool OnMouseButtonPress(MouseButtonPressedEvent& e);
		bool OnMouseButtonRelease(MouseButtonReleasedEvent& e);
		bool OnMouseScroll(MouseScrolledEvent& e);
		bool OnKeyPress(KeyPressedEvent& e);
		bool OnKeyRelease(KeyReleasedEvent& e);

	protected:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		Renderer m_Renderer;

		float m_CurrentFrame, m_LastFrame;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}