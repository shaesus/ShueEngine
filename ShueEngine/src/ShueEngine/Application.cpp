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

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}

}