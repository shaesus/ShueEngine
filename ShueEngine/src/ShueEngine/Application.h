#pragma once
#include "Core.h"

#include <memory>

#include "Window.h"
#include "Renderer.h"

namespace Shue {

	class SHUE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
	protected:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		Renderer m_Renderer;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}