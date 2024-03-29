#include "Application.h"

#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw.h"
#include "imGUI/imgui_impl_opengl3.h"

#include <iostream>
#include <map>
#include <format>

namespace Shue {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
		: m_CurrentFrame(0), m_LastFrame(0)
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	float lastX = 0;
	float lastY = 0;

	bool firstMouse = true;

	Camera* camera = new Camera();

	void Application::Run()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		m_Renderer.SetBlending(true);
		m_Renderer.SetDepthTest(true);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(m_Window->GetGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		m_Renderer.SetCulling(true, GL_BACK);
		m_Renderer.SetFrontFace(GL_CCW);

		float cubeVertices[] = {
			// Back face
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // bottom-right         
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top-right
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // bottom-left
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // top-left
			// Front face							   
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // top-right
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // top-right
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // top-left
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
			// Left face							   
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-right
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // top-left
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-left
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-left
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // bottom-right
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-right
			// Right face							   
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // top-left
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-right         
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // top-left
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-left     
			 // Bottom face							   
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // top-left
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // bottom-left
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // top-right
			// Top face			  					   
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // top-left
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // top-right     
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // top-left
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // bottom-left        
		};					  						   
													   
		VertexArray cubeVA;							   
		VertexBuffer cubeVB(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		cubeVA.AddBuffer(cubeVB, layout);

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)m_Window->GetWidth() / (float)m_Window->GetHeight()
			, 0.1f, 100.0f);
		glm::mat4 view;

		glm::vec3 cubePos(-0.15f, -0.2f, -0.9f);
		
		Shader lightingShader("res/shaders/Lighting.shader");
		lightingShader.Bind();

		ImageTexture diamondOreTex("res/textures/diamond_ore.png");
		
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

		glm::vec3 lightSourcePos(0.2f, -0.2f, -1.0f);

		Shader lightSourceShader("res/shaders/LightSource.shader");
		lightSourceShader.Bind();

		ImageTexture redstoneLampTex("res/textures/redstone_lamp.png");

		float lightSourceVertices[] = {
			// Back face
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right         
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top-left
			// Front face
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // top-right
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // top-right
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // top-left
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-left
			// Left face
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // top-right
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top-left
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // top-right
			// Right face
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // top-left
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right         
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // top-left
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-left     
			 // Bottom face
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-left
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-left
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-right
			// Top face			
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top-left
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right     
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top-left
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // bottom-left        
		};

		VertexArray lightSourceVA;
		lightSourceVA.Bind();

		VertexBuffer lightSourceVB(sizeof(lightSourceVertices), lightSourceVertices, GL_STATIC_DRAW);

		VertexBufferLayout lightSourceLayout;
		lightSourceLayout.Push<float>(3);
		lightSourceLayout.Push<float>(2);
		lightSourceVA.AddBuffer(lightSourceVB, lightSourceLayout);

		lightingShader.Unbind();
		cubeVA.Unbind();
		cubeVB.Unbind();
		shaderText.Unbind();
		vaText.Unbind();
		vbText.Unbind();
		lightSourceShader.Unbind();
		lightSourceVA.Unbind();
		lightSourceVB.Unbind();

		int framesCount = 0;

		glm::vec3 objectColor(1.0f, 0.5f, 0.31f);
		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

		while (m_Running)
		{
			m_Running = !glfwWindowShouldClose(m_Window->GetGLFWWindow());

			m_Renderer.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			m_Renderer.Clear();

			view = glm::lookAt(camera->Position, camera->Position + camera->Front, camera->Up);

			lightSourcePos.y = sin(glfwGetTime()) / 3.0f - 0.2f;

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePos);
				model = glm::scale(model, glm::vec3(0.25f));
				lightingShader.Bind();
				lightingShader.SetUniformMatrix4fv("u_Model", model);
				lightingShader.SetUniformMatrix4fv("u_View", view);
				lightingShader.SetUniformMatrix4fv("u_Proj", proj);
				lightingShader.SetUniformVec3("u_ObjectColor", objectColor);
				lightingShader.SetUniformVec3("u_LightColor", lightColor);
				lightingShader.SetUniformVec3("u_LightPos", lightSourcePos);
				lightingShader.SetUniformVec3("u_ViewPos", camera->Position);
				diamondOreTex.Bind(0);
				lightingShader.SetUniform1i("u_Texture", 0);
				m_Renderer.DrawTriangles(cubeVA, lightingShader, sizeof(cubeVertices));
				lightingShader.Unbind();
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), lightSourcePos);
				model = glm::scale(model, glm::vec3(0.1f));
				glm::mat4 mvp = proj * view * model;
				lightSourceShader.Bind();
				redstoneLampTex.Bind(1);
				lightSourceShader.SetUniform1i("u_Texture", 1);
				lightSourceShader.SetUniformMatrix4fv("u_MVP", mvp);
				m_Renderer.DrawTriangles(lightSourceVA, lightSourceShader, sizeof(lightSourceVertices));
				lightSourceShader.Unbind();
			}

			shaderText.Bind();
			shaderText.SetUniformMatrix4fv("u_Projection", projText);

			m_Renderer.RenderText(vaText, vbText, shaderText, "Frames since start: " + std::to_string(framesCount), 1.0f, 1.0f, 0.7f, glm::vec3(1.0f, 0.5f, 0.3f), "arial");

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			{
				ImGui::Begin("Positions");
				ImGui::SliderFloat3("Translation A", &cubePos.x, -1.0f, 1.0f);
				ImGui::SliderFloat3("Translation B", &lightSourcePos.x, -1.0f, 1.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}

			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			AppUpdateEvent appUpdateEvent;
			OnEvent(appUpdateEvent);

			framesCount++;
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
		dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(OnUpdate));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMove));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPress));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseButtonRelease));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScroll));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPress));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnKeyRelease));

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
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
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

	bool Application::OnUpdate(AppUpdateEvent& e)
	{
		m_LastFrame = m_CurrentFrame;
		m_CurrentFrame = glfwGetTime();

		camera->OnUpdate(DeltaTime());

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_Window->OnUpdate();

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
		
		camera->ProcessMouseMovement(xoffset, yoffset, true);

		return true;
	}

	bool Application::OnMouseButtonPress(MouseButtonPressedEvent& e)
	{
		std::cout << e << std::endl;

		camera->ProcessPressedMouseButton(e.GetMouseButton());

		return true;
	}

	bool Application::OnMouseButtonRelease(MouseButtonReleasedEvent& e)
	{
		std::cout << e << std::endl;

		camera->ProcessReleasedMouseButton(e.GetMouseButton());

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

		camera->ProcessPressedKey(e.GetKeyCode());

		return true;
	}

	bool Application::OnKeyRelease(KeyReleasedEvent& e)
	{
		std::cout << e << std::endl;

		camera->ProcessReleasedKey(e.GetKeyCode());

		return true;
	}

}