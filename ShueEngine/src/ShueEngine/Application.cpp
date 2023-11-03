#include "Application.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Shue {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Renderer.SetBlending(true);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
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

		Shue::VertexArray va;
		Shue::VertexBuffer vb(sizeof(vertices), vertices);

		Shue::VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		Shue::IndexBuffer ib(sizeof(indices), indices);
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)m_Window->GetWidth() / (float)m_Window->GetHeight()
			, 0.1f, 100.0f);
		glm::mat4 view = glm::mat4(1.0f);

		glm::vec3 translationA(-0.45f, -0.2f, -1.0f);
		glm::vec3 translationB(0.0f, 0.0f, -1.0f);

		float viewRotationY = 0;
		float viewRotationX = 0;

		Shue::Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		shader.Unbind();
		va.Unbind();
		vb.Unbind();
		ib.Unbind();

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

			m_Window->OnUpdate();
		}
	}

}