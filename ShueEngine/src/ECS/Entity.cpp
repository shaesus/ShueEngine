#include "Entity.h"

namespace Shue {

	Entity::Entity()
	{
		unsigned int id = ++s_MaxID;
		while (s_IDs.contains(id))
			id = ++s_MaxID;

		m_ID = id;
		s_IDs.insert(id);

		m_Name = "Entity " + std::to_string(id);

		m_Transform = new Transform();
		m_Components.emplace(Transform::GetStaticType(), m_Transform);
	}

	Entity::Entity(const std::string& name) : Entity()
	{
		m_Name = name;
	}

	Entity::~Entity()
	{
		for (auto& [type, comp] : m_Components)
			delete comp;
	}

	void Entity::UpdateComponents()
	{
		for (const auto& [type, comp] : m_Components) 
			comp->Update();
	}

}