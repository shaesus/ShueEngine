#pragma once

#include "Core.h"

#include "Transform.h"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stdexcept>

namespace Shue {

	class SHUE_API Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void UpdateComponents();
		virtual void Update() = 0;

		inline unsigned int GetID() const { return m_ID; }
		inline Transform* GetTransform() { return m_Transform; }

		template<typename T>
		Component* GetComponent() 
		{ 
			auto it = m_Components.find(T::GetStaticType());
			if (it != m_Components.end())
				return it->second; 
		}

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
		inline static std::unordered_set<unsigned int> s_IDs;
		inline static unsigned int s_MaxID;

	protected:
		std::unordered_map<ComponentType, Component*> m_Components;
		unsigned int m_ID;
		Transform* m_Transform;
	};

}