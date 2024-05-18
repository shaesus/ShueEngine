#include "Backpack.h"
#include "ECS/ModelRenderer.h"
#include "ECS/Transform.h"

#include "Application/Application.h"

Backpack::Backpack(const std::string& name, Shue::Model* model, Shue::Shader& shader) : Shue::Entity(name)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(model, shader));
}

Backpack::Backpack(const std::string& name, const std::string& modelPath, Shue::Shader& shader) : Shue::Entity(name)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(modelPath, shader));
}

void Backpack::Update()
{
	m_Transform->Rotate(Shue::TIME_SINCE_START, glm::vec3(0.0f, 1.0f, 0.0f));
}
