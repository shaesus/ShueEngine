#include "Container.h"
#include "ECS/ModelRenderer.h"
#include "ECS/Transform.h"

#include "Application/Application.h"

Container::Container(const std::string& name, Shue::Model* model, Shue::Shader& shader) : Shue::Entity(name)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(model, shader));
}

Container::Container(const std::string& name, const std::string& modelPath, Shue::Shader& shader) : Shue::Entity(name)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(modelPath, shader));
}

void Container::Update()
{
}
