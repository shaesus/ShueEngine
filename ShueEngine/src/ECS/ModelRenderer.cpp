#include "ModelRenderer.h"

#include "Application/Application.h"

namespace Shue {

	ModelRenderer::ModelRenderer(Model* model, Shader& shader)
		: m_Model(model), m_Shader(shader)
	{
	}

	ModelRenderer::ModelRenderer(const std::string& modelPath, Shader& shader)
		: m_Shader(shader)
	{
		m_Model = std::unique_ptr<Model>(new Model(modelPath));
	}

	void ModelRenderer::Update()
	{
		Application::Get().GetRenderer().DrawModel(*m_Model, m_Shader);
	}

	void ModelRenderer::SetModel(Model* model)
	{
		m_Model = std::unique_ptr<Model>(model);
	}

	void ModelRenderer::SetModel(const std::string& modelPath)
	{
		m_Model = std::unique_ptr<Model>(new Model(modelPath));
	}

}