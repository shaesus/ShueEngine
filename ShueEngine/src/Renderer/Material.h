#pragma once

#include "Core.h"

#include "glm/glm.hpp"

namespace Shue {

	class SHUE_API Material
	{
	public:
		Material(int diffuseMap, glm::vec3 specular, float shininess);

		inline const int DiffuseMap() const { return m_DiffuseMap; }
		inline const glm::vec3& Specular() const { return m_Specular; }
		inline float Shininess() const { return m_Shininess; }

	private:
		int m_DiffuseMap;
		glm::vec3 m_Specular;
		float m_Shininess;
	};

}