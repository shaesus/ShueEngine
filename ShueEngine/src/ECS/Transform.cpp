#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Shue {

	Transform::Transform()
	{
		m_ModelMatrix = glm::mat4(1.0f);
		Position = glm::vec3(0.0f);
		Scale = glm::vec3(1.0f);
	}

	void Transform::Update()
	{
		m_ModelMatrix = glm::translate(glm::mat4(1.0f), Position);
		m_ModelMatrix = glm::scale(m_ModelMatrix, Scale);
	}

	void Transform::Rotate(float angle, glm::vec3 localAxis)
	{
		m_ModelMatrix = glm::rotate(m_ModelMatrix, angle, localAxis);
	}

	void Transform::RotateGlobal(float angle, glm::vec3 globalAxis)
	{
		m_ModelMatrix = glm::rotate(glm::mat4(1.0f), angle, globalAxis);
		m_ModelMatrix = glm::translate(m_ModelMatrix, Position);
		m_ModelMatrix = glm::scale(m_ModelMatrix, Scale);
	}

}