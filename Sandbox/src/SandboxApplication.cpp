#include "ShueEngine.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Material.h"
#include "LightProperties.h"
#include "Model.h"

#include "Scene/Scene.h"
#include "Entities/Backpack.h"
#include "Entities/Container.h"
#include "Entities/LightSource.h"

#include "Layers/SandboxUILayer.h"

glm::vec4 backgroundColor (  0.2f,  0.3f,  0.3f, 1.0f );
glm::vec3 containerPos         ( -0.2f, -0.2f,  0.1f );
glm::vec3 lightSourcePos  (  0.2f, -0.2f,  0.0f );
glm::vec3 textPos         (  0.0f, -0.1f, -0.3f );
glm::vec3 lightColor      (  1.0f,  1.0f,  1.0f );
glm::vec3 backpackPos     (  0.0f,  0.0f, -0.3f );

class Sandbox : public Shue::Application
{
public:
	Sandbox() 
	{
		PushOverlay(new SandboxUILayer());
	}

	void Run() override
	{
		m_Renderer.InitGlad();

		m_Renderer.SetBlending(true);
		m_Renderer.SetDepthTest(true);

		m_Renderer.SetCulling(true, GL_BACK);
		m_Renderer.SetFrontFace(GL_CCW);

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)m_Window->GetWidth() / (float)m_Window->GetHeight()
			, 0.1f, 100.0f);
		glm::mat4 view;

#ifdef RENDER_TEXT
		m_Renderer.InitFreeType();

		m_Renderer.AddFont("res/fonts/arial.ttf", "arial");
		m_Renderer.AddFont("res/fonts/comic.ttf", "comic");

		glm::mat4 projText = glm::ortho(0.0f, (float)m_Window->GetWidth(), 0.0f, (float)m_Window->GetHeight());

		Shue::VertexArray vaTextWS;
		Shue::VertexBuffer vbTextWS(sizeof(float) * 6 * 5, NULL, GL_DYNAMIC_DRAW);

		Shue::VertexBufferLayout layoutTextWS;
		layoutTextWS.Push<float>(3);
		layoutTextWS.Push<float>(2);
		vaTextWS.AddBuffer(vbTextWS, layoutTextWS);

		Shue::Shader shaderTextWS("res/shaders/WorldSpaceText.shader");
		shaderTextWS.Bind();

		Shue::VertexArray vaText;
		Shue::VertexBuffer vbText(sizeof(float) * 6 * 5, NULL, GL_DYNAMIC_DRAW);

		Shue::VertexBufferLayout layoutText;
		layoutText.Push<float>(3);
		layoutText.Push<float>(2);
		vaText.AddBuffer(vbText, layoutText);

		Shue::Shader shaderText("res/shaders/Text.shader");
		shaderText.Bind();
#endif

		Shue::Model lightSourceModel("res/models/LightSource/LightSource.obj");
		Shue::Shader lightSourceShader("res/shaders/LightSource.shader");
		LightSource* lightSource = new LightSource("Light Source", &lightSourceModel, lightSourceShader);
		CurrentScene.AddObject(lightSource);

		Shue::Transform* lightSourceTransform = lightSource->GetTransform();
		lightSourceTransform->Position = lightSourcePos;
		lightSourceTransform->Scale = glm::vec3(0.05f);

		Shue::Model containerModel("res/models/Container/Container.obj");
		Shue::Shader containerShader("res/shaders/Model.shader");
		Container* container = new Container("Container", &containerModel, containerShader);
		CurrentScene.AddObject(container);

		Shue::Transform* containerTransform = container->GetTransform();
		containerTransform->Position = containerPos;
		containerTransform->Scale = glm::vec3(0.125f);

		Shue::Model backpackModel("res/models/Backpack/backpack.obj");
		Shue::Shader backpackShader("res/shaders/Model.shader");
		Backpack* backpack = new Backpack("Backpack", &backpackModel, backpackShader);
		CurrentScene.AddObject(backpack);

		Shue::Transform* backpackTransform = backpack->GetTransform();
		backpackTransform->Position = backpackPos;
		backpackTransform->Scale = glm::vec3(0.1f);
		
		Shue::Shader lineShader("res/shaders/Line.shader");

#ifdef RENDER_TEXT
		shaderText.Unbind();
		vaText.Unbind();
		vbText.Unbind();
		shaderTextWS.Unbind();
		vaTextWS.Unbind();
		vbTextWS.Unbind();
#endif
		backpackShader.Unbind();

		while (m_Running)
		{
			m_Renderer.ClearColor(backgroundColor);
			m_Renderer.Clear();

			view = glm::lookAt(Shue::Camera::Main->Position, 
				Shue::Camera::Main->Position + Shue::Camera::Main->Front, Shue::Camera::Main->Up);

			lightSourcePos.y = sin(m_TimeOfCurrentFrame) / 3.0f - 0.2f;

			//Light Source
			{
				lightSourceShader.Bind();
				lightSourceShader.SetUniformMatrix4fv("u_Model", lightSourceTransform->GetModelMatrix());
				lightSourceShader.SetUniformMatrix4fv("u_View", view);
				lightSourceShader.SetUniformMatrix4fv("u_Proj", proj);
			}

			//Container
			{
				containerShader.Bind();
				containerShader.SetUniformMatrix4fv("u_Model", containerTransform->GetModelMatrix());
				containerShader.SetUniformMatrix4fv("u_View", view);
				containerShader.SetUniformMatrix4fv("u_Proj", proj);
				containerShader.SetUniformLightProperties("u_Light",
					Shue::LightProperties(lightSourcePos, glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f)));
				containerShader.SetUniformVec3("u_ViewPos", Shue::Camera::Main->Position);
			}

			//Backpack
			{
				backpackShader.Bind();
				backpackShader.SetUniformMatrix4fv("u_Model", backpackTransform->GetModelMatrix());
				backpackShader.SetUniformMatrix4fv("u_View", view);
				backpackShader.SetUniformMatrix4fv("u_Proj", proj);
				backpackShader.SetUniformLightProperties("u_Light",
					Shue::LightProperties(lightSourcePos, glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f)));
				backpackShader.SetUniformVec3("u_ViewPos", Shue::Camera::Main->Position);
			}

#ifdef RENDER_TEXT
			//World Space Text
			{

				glm::mat4 model = glm::translate(glm::mat4(1.0f), textPos);
				glm::mat4 mvp = proj * view * model;
				shaderTextWS.Bind();
				shaderTextWS.SetUniformMatrix4fv("u_MVP", mvp);

				m_Renderer.RenderText(vaTextWS, vbTextWS, shaderTextWS, "World Space", 0.0f, 0.0f, 0.002f, glm::vec3(1.0f, 0.5f, 0.3f), "comic");
			}

			//Screen Space Text
			{
				shaderText.Bind();
				shaderText.SetUniformMatrix4fv("u_Projection", projText);

				m_Renderer.RenderText(vaText, vbText, shaderText, "Screen Space", 1.0f, 1.0f, 0.7f, glm::vec3(1.0f, 0.5f, 0.3f), "arial");
			}
#endif

			Shue::AppUpdateEvent appUpdateEvent;
			OnEvent(appUpdateEvent);
		}
	}

	~Sandbox() 
	{
	}
};

Shue::Application* Shue::CreateApplication()
{
	return new Sandbox();
}