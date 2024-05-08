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
		m_Model = new Model(modelPath);
	}

	void ModelRenderer::Update()
	{
		Application::Get().GetRenderer().DrawModel(*m_Model, m_Shader);
	}

}