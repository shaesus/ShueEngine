#include "Core.h"

#include "Component.h"
#include "Model.h"
#include "Shader.h"

#include <string>

namespace Shue {

	class SHUE_API ModelRenderer : public Component
	{
	public:
		ModelRenderer(Model* model, Shader& shader);
		ModelRenderer(const std::string& modelPath, Shader& shader);

		void Update() override;
		void SetModel(Model* m_Model);
		void SetModel(const std::string& modelPath);

		inline Shader& GetShader() { return m_Shader; }

		COMPONENT_CLASS_TYPE(ModelRendererComp)

	private:
		Model* m_Model;
		Shader& m_Shader;
	};

}