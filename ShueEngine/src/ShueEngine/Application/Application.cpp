#include "Application.h"

#include "Core.h"
#include "Assertion.h"

#include <iostream>

namespace Shue {

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
		: m_TimeOfCurrentFrame(0), m_TimeOfLastFrame(0)
	{
		ASSERT(!s_Instance);
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(SH_BIND_EVENT_FN(Application::OnEvent));

		CurrentScene = Scene("SampleScene");
		Camera::Main = new Camera(glm::vec3(0.0f, 0.0f, 1.0f));
	}

	Application::~Application()
	{
	}

	static float lastX = 0;
	static float lastY = 0;

	bool firstMouse = true;

	void Application::Run()
	{	
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(SH_BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<WindowCloseEvent>(SH_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<AppUpdateEvent>(SH_BIND_EVENT_FN(Application::OnUpdate));
		dispatcher.Dispatch<MouseMovedEvent>(SH_BIND_EVENT_FN(Application::OnMouseMove));
		dispatcher.Dispatch<MouseButtonPressedEvent>(SH_BIND_EVENT_FN(Application::OnMouseButtonPress));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(SH_BIND_EVENT_FN(Application::OnMouseButtonRelease));
		dispatcher.Dispatch<MouseScrolledEvent>(SH_BIND_EVENT_FN(Application::OnMouseScroll));
		dispatcher.Dispatch<KeyPressedEvent>(SH_BIND_EVENT_FN(Application::OnKeyPress));
		dispatcher.Dispatch<KeyTypedEvent>(SH_BIND_EVENT_FN(Application::OnKeyType));
		dispatcher.Dispatch<KeyReleasedEvent>(SH_BIND_EVENT_FN(Application::OnKeyRelease));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		GLCall(glViewport(0, 0, e.GetWidth(), e.GetHeight()));
		return true;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnUpdate(AppUpdateEvent& e)
	{
		m_TimeOfLastFrame = m_TimeOfCurrentFrame;
		m_TimeOfCurrentFrame = glfwGetTime();

		Camera::Main->OnUpdate();
		CurrentScene.OnUpdate();

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_Window->OnUpdate();

		m_Running = !glfwWindowShouldClose(m_Window->GetGLFWWindow());

		return true;
	}

	bool Application::OnMouseMove(MouseMovedEvent& e)
	{
		if (firstMouse)
		{
			lastX = e.GetX();
			lastY = e.GetY();
			firstMouse = false;
		}

		float xoffset = e.GetX() - lastX;
		float yoffset = lastY - e.GetY();
		lastX = e.GetX();
		lastY = e.GetY();
		
		Camera::Main->ProcessMouseMovement(xoffset, yoffset, true);

		return true;
	}

	bool Application::OnMouseButtonPress(MouseButtonPressedEvent& e)
	{
		Camera::Main->ProcessPressedMouseButton(e.GetMouseButton());

		return true;
	}

	bool Application::OnMouseButtonRelease(MouseButtonReleasedEvent& e)
	{
		Camera::Main->ProcessReleasedMouseButton(e.GetMouseButton());

		return true;
	}

	bool Application::OnMouseScroll(MouseScrolledEvent& e)
	{
		return true;
	}

	bool Application::OnKeyPress(KeyPressedEvent& e)
	{
		Camera::Main->ProcessPressedKey(e.GetKeyCode());

		return true;
	}

	bool Application::OnKeyType(KeyTypedEvent& e)
	{
		return true;
	}

	bool Application::OnKeyRelease(KeyReleasedEvent& e)
	{
		Camera::Main->ProcessReleasedKey(e.GetKeyCode());

		return true;
	}

}