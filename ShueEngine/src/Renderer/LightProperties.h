#pragma once

#include "Core.h"

#include "glm/glm.hpp"

namespace Shue {

	class SHUE_API LightProperties
	{
	public:
		LightProperties(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

		inline const glm::vec3& Position() const { return m_Pos; }
		inline const glm::vec3& Ambient() const { return m_Ambient; }
		inline const glm::vec3& Diffuse() const { return m_Diffuse; }
		inline const glm::vec3& Specular() const { return m_Specular; }

	private:
		glm::vec3 m_Pos;
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
	};

}