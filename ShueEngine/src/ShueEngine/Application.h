#pragma once
#include "Core.h"

#include <memory>

#include "Window.h"
#include "Renderer/Renderer.h"

namespace Shue {

	class SHUE_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		Renderer m_Renderer;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}