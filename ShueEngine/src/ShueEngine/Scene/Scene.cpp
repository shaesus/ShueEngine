#include "Scene.h"

#include <utility>

namespace Shue {
	Scene::Scene(const std::string& name)
		: m_Name(name) {}

	Scene::~Scene()
	{
		for (auto& [id, entity] : m_sceneObjects)
			delete entity;
	}

	void Scene::OnUpdate()
	{
		for (auto& [id, entity] : m_sceneObjects)
		{
			entity->UpdateComponents();
			entity->Update();
		}
	}

	void Scene::AddObject(Entity* entity)
	{
		m_sceneObjects.insert(std::pair(entity->GetID(), entity));
	}

}