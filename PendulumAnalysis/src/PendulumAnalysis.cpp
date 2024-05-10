#include "ShueEngine.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Material.h"
#include "LightProperties.h"

#include "Entities/Pendulum.h"
#include "ECS/ModelRenderer.h"

#include "Layers/PendulumUILayer.h"

#include "MySQL/MySQLConnection.h"

#include <string>
#include <unordered_map>

glm::vec4 backgroundColor (  0.2f,  0.3f, 0.3f, 1.0f );
glm::vec3 cubePos         ( -0.2f, -0.2f, 0.1f );
glm::vec3 lightSourcePos  (  0.0f,  1.0f, 0.0f );
glm::vec3 lightColor      (  1.0f,  1.0f, 1.0f );
glm::vec3 spherePos       (  0.0f,  0.0f, 0.0f );

static float mass = 2.0f;
static float length = 2.0f;
static float startAngle = 45.0f;

static const float massScaleCoeff = 0.05f;
static const float lengthYCoeff = -0.15f;

static Pendulum** pendulum = new Pendulum*;

static UIData uiData;

static std::unordered_map<std::string, Shue::Model*> loadedModels;

static void SetupPendulum(Pendulum* pendulum, Shue::Transform* pendulumTransform);

class PendulumAnalysis : public Shue::Application
{
public:
	PendulumAnalysis()
	{
		PushOverlay(new PendulumUILayer(pendulum, mass, length, startAngle, uiData));
	}

	void Run() override
	{
		m_Renderer.InitGlad();

		m_Renderer.SetBlending(true);
		m_Renderer.SetDepthTest(true);

		m_Renderer.SetCulling(true, GL_BACK);
		m_Renderer.SetFrontFace(GL_CCW);

		Shue::MySQLConnection::MakeConnection("tcp://127.0.0.1:3306", "root", "okcomputer", "PendulumAnalysis");

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)m_Window->GetWidth() / (float)m_Window->GetHeight()
			, 0.1f, 100.0f);
		glm::mat4 view;

		Shue::ImageTexture* pendulumTexture = new Shue::ImageTexture("res/textures/orange.jpg");

		Shue::Shader pendulumShader("res/shaders/Lighting.shader");
		pendulumShader.Bind();
		pendulumShader.SetUniformMaterial("u_Material", Shue::Material(3, 3, 32.0f));

		Shue::Model* pendulumModel = new Shue::Model("res/models/Sphere/Sphere.obj");

		*pendulum = new Pendulum(pendulumModel, pendulumShader, mass, length, startAngle);
		CurrentScene.AddObject(*pendulum);

		Shue::ModelRenderer* pendulumModelRenderer;

		Shue::Transform* pendulumTransform = (*pendulum)->GetTransform();
		SetupPendulum(*pendulum, pendulumTransform);

		Shue::Shader lineShader("res/shaders/Line.shader");
		lineShader.Bind();
		lineShader.SetUniformVec4("u_Color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		Shue::VertexArray lineVA = m_Renderer.GetLineVA(0.0f, 0.0f, 0.0f, spherePos.x, spherePos.y, spherePos.z);

		pendulumShader.Unbind();
		lineShader.Unbind();

		while (m_Running)
		{
			m_Renderer.ClearColor(backgroundColor);
			m_Renderer.Clear();

			view = glm::lookAt(Shue::Camera::Main->Position,
				Shue::Camera::Main->Position + Shue::Camera::Main->Front, Shue::Camera::Main->Up);

			if (uiData.confirmed)
			{
				CurrentScene.RemoveObject((*pendulum)->GetID());
				delete* pendulum;
				*pendulum = new Pendulum(pendulumModel, pendulumShader, mass, length, startAngle);
				CurrentScene.AddObject(*pendulum);
				pendulumTransform = (*pendulum)->GetTransform();
				SetupPendulum(*pendulum, pendulumTransform);
				lineVA = m_Renderer.GetLineVA(0.0f, 0.0f, 0.0f, spherePos.x, spherePos.y, spherePos.z);
			}

			if (uiData.getTable)
				Shue::MySQLConnection::ExecuteQuery("select * from PendulumData");

			if (uiData.fileSelected)
			{
				if (uiData.filePath.find(".obj") != std::string::npos)
				{
					pendulumModelRenderer = (Shue::ModelRenderer*)((*pendulum)->GetComponent<Shue::ModelRenderer>());
					if (loadedModels.find(uiData.filePath) == loadedModels.end())
						loadedModels.emplace(uiData.filePath, new Shue::Model(uiData.filePath));
					pendulumModelRenderer->SetModel(loadedModels[uiData.filePath]);
				}
				else if (uiData.filePath.find(".png") != std::string::npos || uiData.filePath.find(".jpg") != std::string::npos)
				{
					delete pendulumTexture;
					pendulumTexture = new Shue::ImageTexture(uiData.filePath);
					pendulumTexture->Bind(3);
				}
			}

			//Line
			{
				glm::mat4 model = glm::rotate(glm::mat4(1.0f), (*pendulum)->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
				lineShader.Bind();
				lineShader.SetUniformMatrix4fv("u_Model", model);
				lineShader.SetUniformMatrix4fv("u_View", view);
				lineShader.SetUniformMatrix4fv("u_Proj", proj);
				m_Renderer.DrawLines(lineVA, lineShader, 2);
			}

			//Sphere
			{
				pendulumShader.Bind();
				pendulumShader.SetUniformMatrix4fv("u_Model", pendulumTransform->GetModelMatrix());
				pendulumShader.SetUniformMatrix4fv("u_View", view);
				pendulumShader.SetUniformMatrix4fv("u_Proj", proj);
				pendulumShader.SetUniformLightProperties("u_Light",
					Shue::LightProperties(lightSourcePos, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)));
				pendulumShader.SetUniformVec3("u_ViewPos", Shue::Camera::Main->Position);
				pendulumTexture->Bind(3);
			}

			Shue::AppUpdateEvent appUpdateEvent;
			OnEvent(appUpdateEvent);
		}

		delete* pendulum;
		delete pendulum;

		Shue::MySQLConnection::CloseConnection();
	}

	~PendulumAnalysis()
	{
	}
};

void SetupPendulum(Pendulum* pendulum, Shue::Transform* pendulumTransform)
{
	spherePos.y = length * lengthYCoeff;
	pendulumTransform->Position = spherePos;
	pendulumTransform->Scale = glm::vec3(mass * massScaleCoeff);
}

Shue::Application* Shue::CreateApplication()
{
	return new PendulumAnalysis();
}