#pragma once

#include "Core.h"

#include <string>

namespace Shue {

	enum class ComponentType
	{
		TransformComp,
		ModelRendererComp
	};

#define COMPONENT_CLASS_TYPE(type) static ComponentType GetStaticType() { return ComponentType::##type; }\
								   virtual ComponentType GetType() const override { return GetStaticType(); }\
								   virtual const char* GetName() const override { return #type; }

	class SHUE_API Component
	{
	public:
		virtual ~Component() = default;

		virtual void Update() = 0;
		virtual inline ComponentType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

}