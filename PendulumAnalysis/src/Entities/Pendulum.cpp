#define _USE_MATH_DEFINES

#include "Pendulum.h"

#include <cmath>

#include "Application/Application.h"
#include "ECS/ModelRenderer.h"

static const float g = 9.81;

Pendulum::Pendulum(Shue::Model* model, Shue::Shader& shader, float mass, float length, float startAngle)
	: Pendulum(mass, length, startAngle)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(model, shader));
}

Pendulum::Pendulum(const std::string& modelPath, Shue::Shader& shader, float mass, float length, float startAngle)
	: Pendulum(mass, length, startAngle)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(modelPath, shader));
}

Pendulum::Pendulum(float mass, float length, float startAngle)
	: m_Mass(mass), m_Length(length)
{
	m_StartAngle = startAngle * M_PI / 180;
	m_CurrentAngle = m_StartAngle;

	m_A = m_Length * sin(m_StartAngle);

	m_Hmax = m_A * (1 - cos(m_StartAngle));
	m_Emax = m_Mass * g * m_Hmax;

	m_T = 2 * M_PI * sqrt(m_Length / g);
	m_Freq = 1.0f / m_T;

	m_P = m_Emax;
	m_K = m_Emax - m_P;
}

void Pendulum::Update()
{
	m_CurrentAngle = m_StartAngle * (1 - cos(2 * M_PI / m_T * Shue::TIME)) - m_StartAngle;

	m_P = m_Mass * g * m_Length * (1 - cos(m_CurrentAngle));
	m_K = m_Emax - m_P;

	m_Transform->RotateGlobal(m_CurrentAngle, glm::vec3(0.0f, 0.0f, 1.0f));
}
