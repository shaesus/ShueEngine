#include "LightSource.h"
#include "ECS/ModelRenderer.h"
#include "ECS/Transform.h"

#include "Application/Application.h"

LightSource::LightSource(const std::string& name, Shue::Model* model, Shue::Shader& shader) : Shue::Entity(name)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(model, shader));
}

LightSource::LightSource(const std::string& name, const std::string& modelPath, Shue::Shader& shader) : Shue::Entity(name)
{
	m_Components.emplace(Shue::ComponentType::ModelRendererComp, new Shue::ModelRenderer(modelPath, shader));
}

void LightSource::Update()
{
	m_Transform->Position.y = sin(Shue::TIME_SINCE_START) / 3.0f - 0.2f;
}
