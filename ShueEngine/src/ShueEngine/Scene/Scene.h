#pragma once

#include "Core.h"

#include "../../ECS/Entity.h"

#include "Assertion.h"

#include <unordered_map>
#include <vector>
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

		std::vector<const char*> GetObjectsList() const;

		std::unordered_map<unsigned int, Entity*>::const_iterator begin() const { return m_SceneObjects.cbegin(); }
		std::unordered_map<unsigned int, Entity*>::const_iterator end() const { return m_SceneObjects.cend(); }

		Entity* operator[](unsigned int id);
		Entity* operator[](const std::string& name);

	private:
		std::string m_Name;
		std::unordered_map<unsigned int, Entity*> m_SceneObjects;
		std::unordered_map<std::string, unsigned int> m_ObjectsIDs;
	};

}