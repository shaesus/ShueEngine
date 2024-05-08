#include "ShueEngine.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Material.h"
#include "LightProperties.h"

#include "Entities/Pendulum.h"

#include "Layers/PendulumUILayer.h"

#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_opengl3.h"

glm::vec4 backgroundColor(0.2f, 0.3f, 0.3f, 1.0f);
glm::vec3 cubePos        (-0.2f, -0.2f, 0.1f);
glm::vec3 lightSourcePos (0.0f, 1.0f, 0.0f);
glm::vec3 lightColor     (1.0f, 1.0f, 1.0f);
glm::vec3 spherePos      (0.0f, -0.3f, 0.0f);

static float mass = 1.0f;
static float length = 1.0f;
static float startAngle = 45.0f;
static bool confirmed;

class PendulumAnalysis : public Shue::Application
{
public:
	PendulumAnalysis()
	{
		PushOverlay(new PendulumUILayer(mass, length, startAngle, confirmed));
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

		Shue::ImageTexture metalTex("res/textures/metal.jpg");
		metalTex.Bind(3);

		Shue::Shader pendulumShader("res/shaders/Lighting.shader");
		pendulumShader.Bind();
		pendulumShader.SetUniformMaterial("u_Material", Shue::Material(3, 3, 32.0f));

		Shue::Model* pendulumModel = new Shue::Model("res/models/Sphere/Sphere.obj");

		Pendulum* pendulum = new Pendulum("res/models/Sphere/Sphere.obj", pendulumShader, mass, length, startAngle);
		CurrentScene.AddObject(pendulum);

		//Shue::Transform* pendulumTransform = pendulum->GetTransform();
		//pendulumTransform->Position = spherePos;
		//pendulumTransform->Scale = glm::vec3(0.1f);

		pendulumShader.Unbind();

		while (m_Running)
		{
			m_Renderer.ClearColor(backgroundColor);
			m_Renderer.Clear();

			view = glm::lookAt(Shue::Camera::Main->Position,
				Shue::Camera::Main->Position + Shue::Camera::Main->Front, Shue::Camera::Main->Up);

			if (confirmed)
			{
				CurrentScene.RemoveObject(pendulum->GetID());
				delete pendulum;
				pendulum = new Pendulum(pendulumModel, pendulumShader, mass, length, startAngle);
				CurrentScene.AddObject(pendulum);
			}

			//Sphere
			{
				glm::mat4 model = glm::rotate(glm::mat4(1.0f), pendulum->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::translate(model, spherePos);
				model = glm::scale(model, glm::vec3(0.1f));
				pendulumShader.Bind();
				pendulumShader.SetUniformMatrix4fv("u_Model", model);
				pendulumShader.SetUniformMatrix4fv("u_View", view);
				pendulumShader.SetUniformMatrix4fv("u_Proj", proj);
				pendulumShader.SetUniformLightProperties("u_Light",
					Shue::LightProperties(lightSourcePos, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)));
				pendulumShader.SetUniformVec3("u_ViewPos", Shue::Camera::Main->Position);
				metalTex.Bind(3);
			}

			Shue::AppUpdateEvent appUpdateEvent;
			OnEvent(appUpdateEvent);
		}

		delete pendulum;
	}

	~PendulumAnalysis()
	{
	}
};

Shue::Application* Shue::CreateApplication()
{
	return new PendulumAnalysis();
}