#pragma once
#include "Core.h"

#include <memory>

#include "Window.h"
#include "LayerStack.h"
#include "Renderer.h"
#include "Camera.h"

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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline float DeltaTime() const { return m_TimeOfCurrentFrame - m_TimeOfLastFrame; }

		inline static Application& Get() { return *s_Instance; }

	protected:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnUpdate(AppUpdateEvent& e);
		bool OnMouseMove(MouseMovedEvent& e);
		bool OnMouseButtonPress(MouseButtonPressedEvent& e);
		bool OnMouseButtonRelease(MouseButtonReleasedEvent& e);
		bool OnMouseScroll(MouseScrolledEvent& e);
		bool OnKeyPress(KeyPressedEvent& e);
		bool OnKeyType(KeyTypedEvent& e);
		bool OnKeyRelease(KeyReleasedEvent& e);

	protected:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		Renderer m_Renderer;
		Camera* m_Camera;

		float m_TimeOfCurrentFrame, m_TimeOfLastFrame;

	protected:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}