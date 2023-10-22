#pragma once

#include "Core.h"

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Shue {

	struct WindowProps
	{
		int Width, Height;
		std::string Title;

		WindowProps(int width = 1024, int height = 640, std::string title = "ShueEngine")
			: Width(width), Height(height), Title(title) {}
	};

	class SHUE_API Window
	{
	public:
		Window(const WindowProps& props);
		~Window();

		void Init(const WindowProps& props);
		void OnUpdate();
		void SetVsync(bool vsync);
		void Shutdown();

		inline bool IsVSync() const { return m_Data.VSync; }

		static Window* Create(const WindowProps& props = WindowProps());

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			int Width, Height;
			std::string Title;
			bool VSync;
		};

		WindowData m_Data;
	};

}

