#pragma once

#include "Core.h"

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

#include "Events/Event.h"

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
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowProps& props);
		~Window();

		void Init(const WindowProps& props);
		void OnUpdate();
		void SetVsync(bool vsync);
		void Shutdown();

		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		inline bool IsVSync() const { return m_Data.VSync; }
		inline int GetWidth() const { return m_Data.Width; }
		inline int GetHeight() const { return m_Data.Height; }
		inline GLFWwindow* GetGLFWWindow() const { return m_Window; }

		static Window* Create(const WindowProps& props = WindowProps());

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			int Width, Height;
			std::string Title;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}

