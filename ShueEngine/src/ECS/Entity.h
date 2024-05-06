#pragma once

#include "Core.h"

#include "Component.h"
#include "Transform.h"

#include <unordered_map>
#include <string>
#include <stdexcept>

namespace Shue {

	class SHUE_API Entity
	{
	public:
		Entity() { m_Components.emplace(Transform::GetStaticType(), new Transform()); }
		virtual ~Entity() {}

		virtual void Update() = 0;
		void UpdateComponents() { for (const auto& [type, comp] : m_Components) { comp->Update(); } }

		inline Transform* GetTransform() { return (Transform*)m_Components[Transform::GetStaticType()]; }

		template<typename T>
		inline T* GetComponent() { return m_Components[T::GetStaticType()]; }

		template<typename T>
		void RemoveComponent() 
		{ 
			if (T::GetStaticType() == ComponentType::TransformComp) std::runtime_error(false);
			else m_Components.erase(T::GetStaticType());
		}

		template <typename T>
		void AddComponent()
		{
			std::runtime_error(false);
		}

	protected:
		std::unordered_map<ComponentType, Component*> m_Components;
	};

}