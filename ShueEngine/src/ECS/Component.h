#pragma once

#include "Core.h"

namespace Shue {

	enum class ComponentType
	{
		TransformComp
	};

#define COMPONENT_CLASS_TYPE(type) static ComponentType GetStaticType() { return ComponentType::##type; }

	class SHUE_API Component
	{
	public:
		virtual ~Component() {}

		virtual void Update() = 0;
		virtual inline ComponentType GetType() = 0;
	};

}