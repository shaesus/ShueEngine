#include "Transform.h"

namespace Shue {

	Transform::Transform()
	{
		Position = glm::vec3(0.0f);
		Scale = glm::vec3(1.0f);
	}

	void Transform::Update()
	{
	}

	ComponentType Transform::GetType()
	{
		return ComponentType::TransformComp;
	}

}