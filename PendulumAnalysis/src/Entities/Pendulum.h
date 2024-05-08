#pragma once

#include "ECS/Entity.h"
#include "Model.h"
#include "Shader.h"

#include <utility>

class Pendulum : public Shue::Entity
{
public:
	Pendulum(Shue::Model* model, Shue::Shader& shader, float mass, float length, float startAngle);
	Pendulum(const std::string& modelPath, Shue::Shader& shader, float mass, float length, float startAngle);

	void Update() override;

	inline float GetAngle() const { return m_CurrentAngle; }

private:
	Pendulum(float mass, float length, float startAngle);

private:
	float m_Mass;
	float m_Length;
	float m_StartAngle;
	float m_CurrentAngle;

	float m_A;
	float m_Emax;
	float m_Hmax;
	float m_T;
	float m_Freq;

	float m_P;
	float m_K;
};