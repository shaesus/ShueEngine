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
		void RemoveObject(unsigned int id);

		inline const std::string& GetName() const { return m_Name; }

		std::unordered_map<unsigned int, Entity*>::const_iterator begin() const { return m_sceneObjects.cbegin(); }
		std::unordered_map<unsigned int, Entity*>::const_iterator end() const { return m_sceneObjects.cend(); }

	private:
		std::string m_Name;
		std::unordered_map<unsigned int, Entity*> m_sceneObjects;
	};

}