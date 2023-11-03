#include "Application.h"

namespace Shue {

	Application::Application()
	{
		m_Renderer.InitGLFW();
		m_Renderer.GLFWSetOpenGLVersionAndProfile(4, 6, GLFW_OPENGL_CORE_PROFILE);

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Renderer.InitGLAD();
		m_Renderer.SetBlending(true);
	}

	Application::~Application()
	{
		m_Renderer.Shutdown();
	}

	void Application::Run()
	{
		while (m_Running);
	}

}