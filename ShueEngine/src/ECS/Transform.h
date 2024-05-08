#pragma once

#include "Core.h"

#include "Component.h"

#include "glm/glm.hpp"

namespace Shue {

	class SHUE_API Transform : public Component
	{
	public:
		Transform();

		void Update() override;

		void Rotate(float angle, glm::vec3 axis);

		inline const glm::mat4& GetModelMatrix() { return m_ModelMatrix; }
	
		COMPONENT_CLASS_TYPE(TransformComp)

	public:
		glm::vec3 Position;
		glm::vec3 Scale;

	private:
		glm::mat4 m_ModelMatrix;
	};

}