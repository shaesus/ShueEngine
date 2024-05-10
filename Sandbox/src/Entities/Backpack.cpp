#include "Backpack.h"
#include "ECS/ModelRenderer.h"
#include "ECS/Transform.h"

#include "Application/Application.h"

Backpack::Backpack(Shue::Model* model, Shue::Shader& shader)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(model, shader));
}

Backpack::Backpack(const std::string& modelPath, Shue::Shader& shader)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(modelPath, shader));
}

void Backpack::Update()
{
	m_Transform->Rotate(Shue::TIME_SINCE_START, glm::vec3(0.0f, 1.0f, 0.0f));
}
