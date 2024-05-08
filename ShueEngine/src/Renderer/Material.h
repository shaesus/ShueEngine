#pragma once

#include "Core.h"

#include "glm/glm.hpp"

namespace Shue {

	class SHUE_API Material
	{
	public:
		Material(int diffuseMap, int specularMap, float shininess)
			: m_DiffuseMap(diffuseMap), m_SpecularMap(specularMap), m_Shininess(shininess) {}

		inline int DiffuseMap() const { return m_DiffuseMap; }
		inline int SpecularMap() const { return m_SpecularMap; }
		inline float Shininess() const { return m_Shininess; }

	private:
		int m_DiffuseMap;
		int m_SpecularMap;
		float m_Shininess;
	};

}