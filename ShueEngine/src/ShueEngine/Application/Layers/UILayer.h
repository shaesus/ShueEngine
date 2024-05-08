#pragma once

#include "Application/ImGui/ImGuiLayer.h"

#include "glm/glm.hpp"

namespace Shue {

	class SHUE_API UILayer : public ImGuiLayer
	{
	public:
		UILayer(glm::vec3& cube, glm::vec3& light);
		~UILayer();

		void OnUpdate() override;

	private:
		glm::vec3& m_cube;
		glm::vec3& m_light;
	};

}