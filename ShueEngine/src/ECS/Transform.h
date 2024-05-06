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
		ComponentType GetType() override;
	
		COMPONENT_CLASS_TYPE(TransformComp)

	public:
		glm::vec3 Position;
		glm::vec3 Scale;
	};

}