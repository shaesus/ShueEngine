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
	inline float GetAngleDeg() const { return m_CurrentAngleDeg; }

	inline float GetAmplitude() const { return m_A; }
	inline float GetEmax() const { return m_Emax; }
	inline float GetHmax() const { return m_Hmax; }
	inline float GetPeriod() const { return m_T; }
	inline float GetFrequency() const { return m_Freq; }
	inline float GetPotentialEnergy() const { return m_P; }
	inline float GetKineticEnergy() const { return m_K; }

private:
	Pendulum(float mass, float length, float startAngle);

private:
	float m_Mass;
	float m_Length;
	float m_StartAngle;
	float m_CurrentAngle;
	float m_CurrentAngleDeg;

	float m_A;
	float m_Emax;
	float m_Hmax;
	float m_T;
	float m_Freq;

	float m_P;
	float m_K;
};