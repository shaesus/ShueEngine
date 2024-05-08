#pragma once

#include "Core.h"

#include "../../ECS/Entity.h"

#include <unordered_map>
#include <string>

namespace Shue {

	class SHUE_API Scene
	{
	public:
		Scene() : m_Name("Scene") {}
		Scene(const std::string& name);
		~Scene();

		void OnUpdate();

		void AddObject(Entity* entity);

		inline const std::string& GetName() const { return m_Name; }

	private:
		std::string m_Name;
		std::unordered_map<unsigned int, Entity*> m_sceneObjects;
	};

}