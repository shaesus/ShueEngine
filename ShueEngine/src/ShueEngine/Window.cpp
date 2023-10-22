#include "Window.h"

#include <iostream>

#include <glad/glad.h>

namespace Shue {

	Window::Window(const WindowProps& props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		if (m_Window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_Window);
		SetVsync(true);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVsync(bool VSync)
	{
		m_Data.VSync = VSync;
		glfwSwapInterval(VSync ? 1 : 0);
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new Window(props);
	}

}