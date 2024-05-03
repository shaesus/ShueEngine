#include "Application.h"

#include "Core.h"

#include "Assertion.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <map>
#include <format>

#include "Material.h"
#include "LightProperties.h"

#include "Layers/UILayer.h"

namespace Shue {

	Application* Application::s_Instance = nullptr;
	
	glm::vec3 cubePos(-0.2f, -0.2f, 0.1f);
	glm::vec3 lightSourcePos(0.2f, -0.2f, 0.0f);

	Application::Application()
		: m_CurrentFrame(0), m_LastFrame(0)
	{
		ASSERT(!s_Instance);
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(SH_BIND_EVENT_FN(Application::OnEvent));

		PushOverlay(new UILayer(&cubePos, &lightSourcePos));
	}

	Application::~Application()
	{
	}

	float lastX = 0;
	float lastY = 0;

	bool firstMouse = true;

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 1.0f));

	void Application::Run()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		m_Renderer.SetBlending(true);
		m_Renderer.SetDepthTest(true);

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

		Shader lightingShader("res/shaders/Lighting.shader");
		lightingShader.Bind();

		//Material obsidianMat(glm::vec3(0.05375f, 0.05f, 0.06625f), glm::vec3(0.18275f, 0.17f, 0.22525f), glm::vec3(0.332741f, 0.328634f, 0.346435f), 0.3f);
		//Material emeraldMat(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f);
		//Material goldMat(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f), 0.4f);
		//Material chromeMat(glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.774597f, 0.774597f, 0.774597f), 0.6f);
		//Material myMat(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);

		ImageTexture containerTex("res/textures/container.png");
		containerTex.Bind(0);

		ImageTexture containerSpecular("res/textures/container2_specular.png");
		containerSpecular.Bind(1);

		lightingShader.SetUniformMaterial("u_Material", Material(0, 1, 32.0f));

		/*FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return;
		}

		m_Renderer.AddFont(ft, "res/fonts/arial.ttf", "arial");
		m_Renderer.AddFont(ft, "res/fonts/comic.ttf", "comic");

		FT_Done_FreeType(ft);*/

		glm::mat4 projText = glm::ortho(0.0f, (float)m_Window->GetWidth(), 0.0f, (float)m_Window->GetHeight());

		VertexArray vaText;
		VertexBuffer vbText(sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

		VertexBufferLayout layoutText;
		layoutText.Push<float>(4);
		vaText.AddBuffer(vbText, layoutText);

		Shader shaderText("res/shaders/Text.shader");
		shaderText.Bind();

		Shader lightSourceShader("res/shaders/LightSource.shader");
		lightSourceShader.Bind();

		ImageTexture redstoneLampTex("res/textures/redstone_lamp.png");
		redstoneLampTex.Bind(2);
		lightSourceShader.SetUniform1i("u_Texture", 2);

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
				lightingShader.SetUniformLightProperties("u_Light", 
					LightProperties(lightSourcePos, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)));
				lightingShader.SetUniformVec3("u_ViewPos", camera->Position);
				containerTex.Bind(0);
				containerSpecular.Bind(1);
				m_Renderer.DrawTriangles(cubeVA, lightingShader, sizeof(cubeVertices));
				lightingShader.Unbind();
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), lightSourcePos);
				model = glm::scale(model, glm::vec3(0.1f));
				glm::mat4 mvp = proj * view * model;
				lightSourceShader.Bind();
				redstoneLampTex.Bind(2);
				lightSourceShader.SetUniformMatrix4fv("u_MVP", mvp);
				m_Renderer.DrawTriangles(lightSourceVA, lightSourceShader, sizeof(lightSourceVertices));
				lightSourceShader.Unbind();
			}

			shaderText.Bind();
			shaderText.SetUniformMatrix4fv("u_Projection", projText);

			//m_Renderer.RenderText(vaText, vbText, shaderText, "Frames since start: " + std::to_string(framesCount), 1.0f, 1.0f, 0.7f, glm::vec3(1.0f, 0.5f, 0.3f), "arial");

			AppUpdateEvent appUpdateEvent;
			OnEvent(appUpdateEvent);
		}

		glfwTerminate();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(SH_BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<WindowCloseEvent>(SH_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<AppUpdateEvent>(SH_BIND_EVENT_FN(Application::OnUpdate));
		dispatcher.Dispatch<MouseMovedEvent>(SH_BIND_EVENT_FN(Application::OnMouseMove));
		dispatcher.Dispatch<MouseButtonPressedEvent>(SH_BIND_EVENT_FN(Application::OnMouseButtonPress));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(SH_BIND_EVENT_FN(Application::OnMouseButtonRelease));
		dispatcher.Dispatch<MouseScrolledEvent>(SH_BIND_EVENT_FN(Application::OnMouseScroll));
		dispatcher.Dispatch<KeyPressedEvent>(SH_BIND_EVENT_FN(Application::OnKeyPress));
		dispatcher.Dispatch<KeyTypedEvent>(SH_BIND_EVENT_FN(Application::OnKeyType));
		dispatcher.Dispatch<KeyReleasedEvent>(SH_BIND_EVENT_FN(Application::OnKeyRelease));

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
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
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
		std::cout << e << '\n';

		camera->ProcessPressedMouseButton(e.GetMouseButton());

		return true;
	}

	bool Application::OnMouseButtonRelease(MouseButtonReleasedEvent& e)
	{
		std::cout << e << '\n';

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
		std::cout << e << '\n';

		camera->ProcessPressedKey(e.GetKeyCode());

		return true;
	}

	bool Application::OnKeyType(KeyTypedEvent& e)
	{
		std::cout << e << '\n';
		return true;
	}

	bool Application::OnKeyRelease(KeyReleasedEvent& e)
	{
		std::cout << e << '\n';

		camera->ProcessReleasedKey(e.GetKeyCode());

		return true;
	}

}