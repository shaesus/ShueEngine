#include "ShueEngine.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Material.h"
#include "LightProperties.h"
#include "Model.h"

#include "Application/Layers/UILayer.h"

glm::vec3 cubePos        ( -0.2f, -0.2f,  0.1f );
glm::vec3 lightSourcePos (  0.2f, -0.2f,  0.0f );
glm::vec3 textPos        (  0.0f, -0.1f, -0.3f );
glm::vec3 backpackPos    (  0.0f,  0.0f, -0.3f );

class Sandbox : public Shue::Application
{
public:
	Sandbox() 
	{
		PushOverlay(new Shue::UILayer(&cubePos, &lightSourcePos));
	}

	void Run() override
	{
		m_Renderer.InitGlad();

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

		Shue::VertexArray cubeVA;
		Shue::VertexBuffer cubeVB(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		Shue::VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		cubeVA.AddBuffer(cubeVB, layout);

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)m_Window->GetWidth() / (float)m_Window->GetHeight()
			, 0.1f, 100.0f);
		glm::mat4 view;

		Shue::Shader lightingShader("res/shaders/Lighting.shader");
		lightingShader.Bind();

		Shue::ImageTexture containerTex("res/textures/container.png");
		containerTex.Bind(0);

		Shue::ImageTexture containerSpecular("res/textures/container2_specular.png");
		containerSpecular.Bind(1);

		lightingShader.SetUniformMaterial("u_Material", Shue::Material(0, 1, 32.0f));

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

		Shue::Shader lightSourceShader("res/shaders/LightSource.shader");
		lightSourceShader.Bind();

		Shue::ImageTexture redstoneLampTex("res/textures/redstone_lamp.png");
		redstoneLampTex.Bind(2);
		lightSourceShader.SetUniform1i("u_Texture", 2);

		Shue::VertexArray lightSourceVA;
		lightSourceVA.Bind();

		Shue::VertexBufferLayout lightSourceLayout;
		lightSourceLayout.Push<float>(3);
		lightSourceLayout.Push<float>(3);
		lightSourceLayout.Push<float>(2);
		lightSourceVA.AddBuffer(cubeVB, lightSourceLayout);

		Shue::Model backpackModel("res/models/Backpack/backpack.obj");

		Shue::ImageTexture backpackDiffuse("res/models/Backpack/diffuse.jpg");
		backpackDiffuse.Bind(3);
		Shue::ImageTexture backpackSpecular("res/models/Backpack/specular.jpg");
		backpackDiffuse.Bind(4);

		Shue::Shader modelShader("res/shaders/Lighting.shader");
		modelShader.Bind();
		modelShader.SetUniformMaterial("u_Material", Shue::Material(3, 4, 20.0f));
		
		lightingShader.Unbind();
		cubeVA.Unbind();
		cubeVB.Unbind();
		shaderText.Unbind();
		vaText.Unbind();
		vbText.Unbind();
		shaderTextWS.Unbind();
		vaTextWS.Unbind();
		vbTextWS.Unbind();
		lightSourceShader.Unbind();
		lightSourceVA.Unbind();
		modelShader.Unbind();

		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

		while (m_Running)
		{
			m_Renderer.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			m_Renderer.Clear();

			view = glm::lookAt(m_Camera->Position, m_Camera->Position + m_Camera->Front, m_Camera->Up);

			lightSourcePos.y = sin(m_TimeOfCurrentFrame) / 3.0f - 0.2f;

			//Backpack
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), backpackPos);
				model = glm::rotate(model, (float)m_TimeOfCurrentFrame, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.1f));
				modelShader.Bind();
				modelShader.SetUniformMatrix4fv("u_Model", model);
				modelShader.SetUniformMatrix4fv("u_View", view);
				modelShader.SetUniformMatrix4fv("u_Proj", proj);
				modelShader.SetUniformLightProperties("u_Light",
					Shue::LightProperties(lightSourcePos, glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f)));
				modelShader.SetUniformVec3("u_ViewPos", m_Camera->Position);
				backpackDiffuse.Bind(3);
				backpackSpecular.Bind(4);
				m_Renderer.DrawModel(backpackModel, modelShader);
			}

			//Cube
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePos);
				model = glm::scale(model, glm::vec3(0.25f));
				lightingShader.Bind();
				lightingShader.SetUniformMatrix4fv("u_Model", model);
				lightingShader.SetUniformMatrix4fv("u_View", view);
				lightingShader.SetUniformMatrix4fv("u_Proj", proj);
				lightingShader.SetUniformLightProperties("u_Light",
					Shue::LightProperties(lightSourcePos, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)));
				lightingShader.SetUniformVec3("u_ViewPos", m_Camera->Position);
				containerTex.Bind(0);
				containerSpecular.Bind(1);
				m_Renderer.DrawTriangles(cubeVA, lightingShader, sizeof(cubeVertices));
			}

			//Light Source
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), lightSourcePos);
				model = glm::scale(model, glm::vec3(0.1f));
				glm::mat4 mvp = proj * view * model;
				lightSourceShader.Bind();
				redstoneLampTex.Bind(2);
				lightSourceShader.SetUniformMatrix4fv("u_MVP", mvp);
				m_Renderer.DrawTriangles(lightSourceVA, lightSourceShader, sizeof(cubeVertices));
			}

			////World Space Text
			//{

			//	glm::mat4 model = glm::translate(glm::mat4(1.0f), textPos);
			//	glm::mat4 mvp = proj * view * model;
			//	shaderTextWS.Bind();
			//	shaderTextWS.SetUniformMatrix4fv("u_MVP", mvp);

			//	m_Renderer.RenderText(vaTextWS, vbTextWS, shaderTextWS, "World Space", 0.0f, 0.0f, 0.002f, glm::vec3(1.0f, 0.5f, 0.3f), "comic");
			//}

			////Screen Space Text
			//{
			//	shaderText.Bind();
			//	shaderText.SetUniformMatrix4fv("u_Projection", projText);

			//	m_Renderer.RenderText(vaText, vbText, shaderText, "Screen Space", 1.0f, 1.0f, 0.7f, glm::vec3(1.0f, 0.5f, 0.3f), "arial");
			//}

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