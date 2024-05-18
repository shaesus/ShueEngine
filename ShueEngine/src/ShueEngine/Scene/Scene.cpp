#include "Scene.h"

#include <utility>

namespace Shue {

	Scene::Scene(const std::string& name)
		: m_Name(name) {}

	Scene::~Scene()
	{
		for (auto& [id, entity] : m_SceneObjects)
			delete entity;
	}

	void Scene::OnUpdate()
	{
		for (auto& [id, entity] : m_SceneObjects)
		{
			entity->UpdateComponents();
			entity->Update();
		}
	}

	void Scene::AddObject(Entity* entity)
	{
		m_SceneObjects.insert(std::pair(entity->GetID(), entity));
		m_ObjectsIDs.insert(std::pair(entity->GetName(), entity->GetID()));
	}

	void Scene::RemoveObject(unsigned int id)
	{
		delete m_SceneObjects[id];
		m_SceneObjects.erase(id);
	}

	std::vector<const char*> Scene::GetObjectsList() const
	{
		std::vector<const char*> vec;
		for (auto it = m_SceneObjects.begin(); it != m_SceneObjects.end(); it++)
			vec.push_back(it->second->GetName().c_str());
		return vec;
	}

	Entity* Scene::operator[](unsigned int id)
	{
		ASSERT(m_SceneObjects.contains(id));
		return m_SceneObjects[id];
	}

	Entity* Scene::operator[](const std::string& name)
	{
		ASSERT(m_ObjectsIDs.contains(name));
		return m_SceneObjects[m_ObjectsIDs[name]];
	}

}