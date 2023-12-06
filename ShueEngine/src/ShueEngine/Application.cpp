#include "Application.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw.h"
#include "imGUI/imgui_impl_opengl3.h"

#include <iostream>
#include <map>

namespace Shue {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		m_Renderer.SetBlending(true);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(m_Window->GetGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		float vertices[] =
		{
			-0.1f, -0.1f, -0.1f, // 0
			-0.1f, -0.1f,  0.1f, // 1
			 0.1f, -0.1f,  0.1f, // 2
			 0.1f, -0.1f, -0.1f, // 3
			-0.1f,  0.1f, -0.1f, // 4
			-0.1f,  0.1f,  0.1f, // 5
			 0.1f,  0.1f,  0.1f, // 6
			 0.1f,  0.1f, -0.1f  // 7
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
			1, 5, 6,
			6, 2, 1,
			0, 4, 5,
			5, 1, 0,
			3, 7, 6,
			6, 2, 3,
			4, 5, 6,
			6, 7, 4,
			0, 4, 7,
			7, 3, 0
		};

		VertexArray va;
		VertexBuffer vb(sizeof(vertices), vertices, GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(sizeof(indices), indices);
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)m_Window->GetWidth() / (float)m_Window->GetHeight()
			, 0.1f, 100.0f);
		glm::mat4 view = glm::mat4(1.0f);

		glm::vec3 translationA(-0.45f, -0.2f, -1.0f);
		glm::vec3 translationB(0.0f, 0.0f, -1.0f);

		float viewRotationY = 0;
		float viewRotationX = 0;

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return;
		}

		m_Renderer.AddFont(ft, "res/fonts/arial.ttf", "arial");
		m_Renderer.AddFont(ft, "res/fonts/comic.ttf", "comic");

		FT_Done_FreeType(ft);

		glm::mat4 projText = glm::ortho(0.0f, (float)m_Window->GetWidth(), 0.0f, (float)m_Window->GetHeight());

		VertexArray vaText;
		VertexBuffer vbText(sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

		VertexBufferLayout layoutText;
		layoutText.Push<float>(4);
		vaText.AddBuffer(vbText, layoutText);

		Shader shaderText("res/shaders/Text.shader");
		shaderText.Bind();

		shader.Unbind();
		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shaderText.Unbind();
		vaText.Unbind();
		vbText.Unbind();

		while (m_Running)
		{
			m_Running = !glfwWindowShouldClose(m_Window->GetGLFWWindow());

			m_Renderer.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			m_Renderer.Clear();

			view = glm::mat4(1.0f);
			view = glm::rotate(view, glm::radians(viewRotationY), glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::rotate(view, glm::radians(viewRotationX), glm::vec3(1.0f, 0.0f, 0.0f));

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 mvp = proj * view * model;
				shader.Bind();
				shader.SetUniform1i("u_Texture", 0);
				shader.SetUniformMatrix4fv("u_MVP", mvp);
				m_Renderer.DrawIb(va, ib, shader);
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 mvp = proj * view * model;
				shader.Bind();
				shader.SetUniform1i("u_Texture", 1);
				shader.SetUniformMatrix4fv("u_MVP", mvp);
				m_Renderer.DrawIb(va, ib, shader);
			}

			shaderText.Bind();
			shaderText.SetUniformMatrix4fv("u_Projection", projText);
			m_Renderer.RenderText(vaText, vbText, shaderText, "Hello, World!", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f), "arial");
			m_Renderer.RenderText(vaText, vbText, shaderText, "Sample Text", 25.0f, 585.0f, 0.75f, glm::vec3(0.5, 0.2f, 0.8f), "comic");

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			{
				ImGui::Begin("Positions");
				ImGui::SliderFloat("Camera Rotation Y", &viewRotationY, -180.0f, 180.0f);
				ImGui::SliderFloat("Camera Rotation X", &viewRotationX, -180.0f, 180.0f);
				ImGui::SliderFloat3("Translation A", &translationA.x, -1.0f, 1.0f);
				ImGui::SliderFloat3("Translation B", &translationB.x, -1.0f, 1.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}

			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			m_Window->OnUpdate();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwTerminate();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMove));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPress));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseButtonRelease));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScroll));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPress));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnKeyRelease));
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		GLCall(glViewport(0, 0, e.GetWidth(), e.GetHeight()));
		std::cout << e << std::endl;
		return true;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		std::cout << e << std::endl;
		return true;
	}

	bool Application::OnMouseMove(MouseMovedEvent& e)
	{
		return true;
	}

	bool Application::OnMouseButtonPress(MouseButtonPressedEvent& e)
	{
		std::cout << e << std::endl;
		return true;
	}

	bool Application::OnMouseButtonRelease(MouseButtonReleasedEvent& e)
	{
		std::cout << e << std::endl;
		return true;
	}

	bool Application::OnMouseScroll(MouseScrolledEvent& e)
	{
		std::cout << e << '\n';
		return true;
	}

	bool Application::OnKeyPress(KeyPressedEvent& e)
	{
		std::cout << e << std::endl;
		return true;
	}

	bool Application::OnKeyRelease(KeyReleasedEvent& e)
	{
		std::cout << e << std::endl;
		return true;
	}

}